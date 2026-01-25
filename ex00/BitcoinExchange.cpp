#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <time.h>

void BitcoinExchange::btc(const char *file)
{
	std::ifstream isCsv("data.csv");
	std::ifstream isTxt(file);
	std::map<int, float> map;

	mapCsv(isCsv, map);
	printBtc(isTxt, map);
}

void BitcoinExchange::mapCsv(std::ifstream& is, std::map<int, float>& map)
{
	std::string line;

	getline(is, line);
	while (getline(is, line))
		mapLine(line, map);
	is.close();
}

void BitcoinExchange::mapLine(std::string& line, std::map<int, float>& map)
{
	int date;
	float value;

	date = getDate(line, ",");
	value = getFloatValue(line, ",", std::numeric_limits<float>::max());
	map[date] = value;
}

float	BitcoinExchange::getFloatValue(const std::string line, const std::string& sep, float max)
{
	size_t found = line.find(sep);
	std::string sub = line.substr(found + sep.size());
	char *ptr;
	float res = std::strtof(sub.c_str(), &ptr);

	if (errno == ERANGE || res > max)
		throw TooLargeNbrException();
	if (res < 0)
		throw NotPositivNbrException();
	if (!ptr || *ptr)
		throw BadFormatException(line);
	return res;
}

int	BitcoinExchange::getDate(std::string& line, const std::string& sep)
{
	size_t found = line.find(sep);
	std::string dateString = line.substr(0, found);

    tm tm = {};

    char *ptr = strptime(dateString.c_str(), "%Y-%m-%d", &tm);
	if (!ptr || *ptr)
		throw BadFormatException(line);
	time_t date = mktime(&tm);
	if (date < 0)
		throw BadFormatException(line);
	return date;
}

void BitcoinExchange::printBtc(std::ifstream& is, std::map<int, float>& map)
{
	std::string line;
	int date;
	float btcAmount;
	bool firstLine = true;

	while (getline(is, line))
	{
		if (firstLine == false || line != "date | value")
		{
			try
			{
				date = getDate(line, " | ");
				btcAmount = getFloatValue(line, " | ", 1000);
				printBtcMapValue(line, map, date, btcAmount);
			}
			catch (std::exception& e)
			{
				std::cout << "Error: " << e.what() << '\n';
			}
		}
		firstLine = false;
	}
}

void	BitcoinExchange::printBtcMapValue(std::string& line, std::map<int, float> map, int date, float nbBtc)
{
	size_t found = line.find(" |");
	line.resize(found);
	for (std::map<int, float>::reverse_iterator it = map.rbegin(); it != map.rend(); it++)
	{
		if (date >= it->first)
		{
			double res = static_cast<double>(it->second) * nbBtc;
			if (res >= std::numeric_limits<double>::max())
				std::cout << line << " => " << nbBtc << " = overflow\n";
			else
				std::cout << line << " => " << nbBtc << " = " << res << '\n';
			return ;
		}
	}
	std::cout << "Error: bitcoin probably didnt exist\n";
}

BitcoinExchange::BadFormatException::BadFormatException(const std::string& error): _error("bad input => " + error) {}

BitcoinExchange::BadFormatException::~BadFormatException() throw() {}

const char* BitcoinExchange::BadExtensionException::what() const throw()
{
	return "bad extension";
}

const char* BitcoinExchange::NotPositivNbrException::what() const throw()
{
	return "not a positive number.";
}

const char* BitcoinExchange::TooLargeNbrException::what() const throw()
{
	return "too large a number.";
}

const char* BitcoinExchange::BadFormatException::what() const throw()
{
	return _error.c_str();
}
