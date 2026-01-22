#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <string>
#include <vector>

class RPN
{
	private:
		RPN();
		~RPN();

		static std::vector<std::string> getTokens(const char*);
		static bool isDigit(std::string&);
		static bool isOperator(std::string&);
		static void pushStack(std::string&, std::stack<long long>&);
		static void operate(std::string&, std::stack<long long>&);

		static long long plus(long long, long long);
		static long long minus(long long, long long);
		static long long multiply(long long, long long);
		static long long divide(long long, long long);
		static long long modulo(long long, long long);

		static const int OPERATIONS_CHOICE = 5;

	public:
		static void rpn(const char*);

	class WrongEntryException: public std::exception
	{
		virtual const char* what() const throw();
	};

	class DivideByZeroException: public std::exception
	{
		virtual const char* what() const throw();
	};
};

#endif
