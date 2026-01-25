#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage ./btc file.csv\n";
		return 1;
	}
	try
	{
		BitcoinExchange::btc(av[1]);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
		return 1;
	}
	return 0;
}
