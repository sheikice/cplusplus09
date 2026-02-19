#include "PmergeMe.hpp"

bool	PmergeMe::isJacobStahlNbr(int nbr)
{
	static const int SIZE_JACOBSTAHL_LIST = 13;
	int	JacobNbr[SIZE_JACOBSTAHL_LIST] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};

	for (size_t i = 0; i < SIZE_JACOBSTAHL_LIST; ++i)
		if (nbr == JacobNbr[i])
			return true;
	return false;
}

void	PmergeMe::checkVal(double nbr, char *end)
{
	if (end && *end)
		throw std::runtime_error("bad arguments");
	if (nbr > INT_MAX)
		throw std::out_of_range("overflow");
}
void PmergeMe::printTime(size_t sizeList, double start, double end, const std::string& type)
{
	double diffTime = end - start;

	std::cout << "Time to process a range of " << sizeList << " elements with " << type << ": " << static_cast<double>(diffTime) << " μs\n";
}

double PmergeMe::getTime()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return time.tv_sec * 1000000 + time.tv_usec;
}
