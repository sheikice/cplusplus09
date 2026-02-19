#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Usage ./PmergeMe 1 2 3 5 233 0 7\n";
		return 1;
	}
	try
	{
		PmergeMe::pMergeMe<std::vector<int>, std::vector<std::pair<int, int> > >(av + 1, "vector");
		PmergeMe::pMergeMe<std::deque<int>, std::deque<std::pair<int, int> > >(av + 1, "deque");
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	}
	return 0;
}
