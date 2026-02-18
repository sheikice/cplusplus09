#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

void RPN::rpn(const char *av)
{
	std::stack<int, std::list<int> > stck;
	std::istringstream iss(av);
	std::string token;

	while (iss >> token)
	{
		if (isDigit(token))
			pushStack(token, stck);
		else if (isOperator(token))
			operate(token, stck);
		else
			throw WrongEntryException();
	}
	if (stck.size() != 1)
		throw WrongEntryException();
	std::cout << "Result = " << stck.top() << '\n';
}

bool RPN::isDigit(std::string& token)
{
	if (token.size() != 1)
		return false;
	if (token.at(0) < '0' || token.at(0) > '9')
		return false;
	return true;
}

bool RPN::isOperator(std::string& token)
{
	std::string operations[5] = {"+", "-", "*", "/"};

	if (token.size() != 1)
		return false;
	for (int i = 0; i < 5; i++)
		if (operations[i] == token)
			return true;
	return false;
}

void RPN::pushStack(std::string& token, std::stack<int, std::list<int> >& stck)
{
	stck.push(std::atoi(token.c_str()));
}

void RPN::operate(std::string& token, std::stack<int, std::list<int> >& stck)
{
	static const int OPERATIONS_CHOICE = 4;

	if (stck.size() < 2)
		throw WrongEntryException();
	typedef int (*ptrFn)(int, int);
	ptrFn func[OPERATIONS_CHOICE] = {&RPN::plus, &RPN::minus, &RPN::multiply, &RPN::divide};
	std::string operations[OPERATIONS_CHOICE] = {"+", "-", "*", "/"};

	int tmp = stck.top();
	stck.pop();
	for (int i = 0; i < OPERATIONS_CHOICE; i++)
		if (operations[i] == token)
			stck.top() = (*func[i])(stck.top(), tmp);
}

int  RPN::plus(int a, int b)
{
	return a + b;
}

int RPN::minus(int a, int b)
{
	return a - b;
}

int RPN::multiply(int a, int b)
{
	return a * b;
}

int RPN::divide(int a, int b)
{
	if (b == 0)
		throw DivideByZeroException();
	long int res = static_cast<long int>(a) / b;
	//./RPN "$(python3 -c 'print("0 1 - " + "2 * " * 63)') 0 1 - /"
	if (res > std::numeric_limits<int>::max() || res < std::numeric_limits<int>::min())
		throw std::out_of_range("overflow has occured in division");
	return res;
}

const char* RPN::WrongEntryException::what() const throw()
{
	return "Wrong entry";
}

const char* RPN::DivideByZeroException::what() const throw()
{
	return "Attempt to divide by zero";
}
