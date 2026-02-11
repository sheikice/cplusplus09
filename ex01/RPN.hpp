#ifndef RPN_HPP
# define RPN_HPP

#include <stack>
#include <string>
#include <vector>
#include <list>

class RPN
{
	private:
		RPN();
		RPN(const RPN&);
		RPN& operator=(const RPN&);
		~RPN();

		static std::vector<std::string> getTokens(const char*);
		static bool isDigit(std::string&);
		static bool isOperator(std::string&);
		static void pushStack(std::string&, std::stack<int, std::list<int> >&);
		static void operate(std::string&, std::stack<int, std::list<int> >&);

		static int plus(int, int);
		static int minus(int, int);
		static int multiply(int, int);
		static int divide(int, int);

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
