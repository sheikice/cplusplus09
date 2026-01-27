#include "PmergeMe.hpp"
#include <iostream>
#include <exception>

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cout << "Usage ./PmergeMe 1 2 3 5 233 0 7\n";
		return 1;
	}
	try
	{
		PmergeMe::pMergeMe(av + 1);
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
