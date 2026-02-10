#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>

void RPN::rpn(const char *av)
{
	std::vector<std::string> tokens = getTokens(av);
	std::stack<long long> stck;

	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++)
	{
		if (isDigit(*it))
			pushStack(*it, stck);
		else if (isOperator(*it))
			operate(*it, stck);
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
	std::string operations[5] = {"+", "-", "*", "/", "%"};

	if (token.size() != 1)
		return false;
	for (int i = 0; i < 5; i++)
		if (operations[i] == token)
			return true;
	return false;
}

void RPN::pushStack(std::string& token, std::stack<long long>& stck)
{
	stck.push(std::atoi(token.c_str()));
}

void RPN::operate(std::string& token, std::stack<long long>& stck)
{
	if (stck.size() < 2)
		throw WrongEntryException();
	typedef long long (*ptrFn)(long long, long long);
	ptrFn func[OPERATIONS_CHOICE] = {&RPN::plus, &RPN::minus, &RPN::multiply, &RPN::divide, &RPN::modulo};
	std::string operations[OPERATIONS_CHOICE] = {"+", "-", "*", "/", "%"};

	long long tmp = stck.top();
	stck.pop();
	for (int i = 0; i < OPERATIONS_CHOICE; i++)
		if (operations[i] == token)
			stck.top() = (*func[i])(stck.top(), tmp);
}

std::vector<std::string> RPN::getTokens(const char *av)
{
	std::istringstream iss(av);
	std::vector<std::string> tokens;
	std::string token;

	while (iss >> token)
		tokens.push_back(token);
	return tokens;
}

long long  RPN::plus(long long a, long long b)
{
	return a + b;
}

long long RPN::minus(long long a, long long b)
{
	return a - b;
}

long long RPN::multiply(long long a, long long b)
{
	return a * b;
}

long long RPN::divide(long long a, long long b)
{
	if (b == 0)
		throw DivideByZeroException();
	if (a == std::numeric_limits<long long>::min() && b == -1)
		throw std::out_of_range("impossible division");
	return a / b;
}

long long RPN::modulo(long long a, long long b)
{
	if (b == 0)
		throw DivideByZeroException();
	//./RPN "$(python3 -c 'print("0 1 - " + "2 * " * 63)') 0 1 - /"
	if (a == std::numeric_limits<long long>::min() && b == -1)
		throw std::out_of_range("impossible division");
	return a % b;
}

const char* RPN::WrongEntryException::what() const throw()
{
	return "Wrong entry";
}

const char* RPN::DivideByZeroException::what() const throw()
{
	return "Attempt to divide by zero";
}
