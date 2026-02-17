#include "RPN.hpp"
#include <iostream>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage ./RPN \"1 2 3 * +\"\n";
		return 1;
	}
	try
	{
			RPN::rpn(av[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
