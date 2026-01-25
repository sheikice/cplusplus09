#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
	private:
		static const int EXTENSION_LETTERS_NBR = 4;
		static const int MONTH_IN_YEAR = 12;

		BitcoinExchange();
		~BitcoinExchange();
		static int getDate(std::string&, const std::string&);
		static float getFloatValue(const std::string line, const std::string& sep, float max);
		static void printBtcMapValue(std::string&, std::map<int, float>, int, float);

		static void mapCsv(std::ifstream&, std::map<int, float>&);
		static void mapLine(std::string&, std::map<int, float>&);
		static void checkFileExtension(const std::string&, const std::string&);
		static void printBtc(std::ifstream&, std::map<int, float>&);

	public:
		static void btc(const char *);

	class BadExtensionException: public std::exception
	{
		virtual const char* what() const throw();
	};

	class BadFormatException: public std::exception
	{
		private:
			std::string _error;
			virtual const char* what() const throw();
		public:
			BadFormatException(const std::string&);
			~BadFormatException() throw();
	};

	class NotPositivNbrException: public std::exception
	{
		virtual const char* what() const throw();
	};

	class TooLargeNbrException: public std::exception
	{
		virtual const char* what() const throw();
	};
};

#endif
