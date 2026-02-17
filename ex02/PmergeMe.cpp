#include "PmergeMe.hpp"

//TODO: two algos
void	PmergeMe::pMergeMe(char** arg)
{
	std::vector<int>	before = strToIntVector(arg);
	std::vector<int>	afterVeq(before);
	std::deque<int>		afterDeq(before.begin(), before.end());

	int	nbCmp = 0;
	double	start = getTime();
	fordJohnSort<std::vector<int>, std::vector<std::pair<int, int> > >(afterVeq, nbCmp);
	double	end = getTime();
	checkSort(afterVeq);

	nbCmp = 0;
	double	start2 = getTime();
	fordJohnSort<std::deque<int>, std::deque<std::pair<int, int> > >(afterDeq, nbCmp);
	double	end2 = getTime();
	checkSort(afterVeq);
	printResult(before, afterVeq, nbCmp);
	printTime(afterVeq.size(), start, end, "std::vector<int> ");
	printTime(afterVeq.size(), start2, end2, "std::deque<int> ");
}

std::vector<int>	PmergeMe::strToIntVector(char **arg)
{
	std::vector<int>	vec;
	char*	end;
	int	size = 0;
	static const int MAX_SIZE = 10000;

	errno = 0;
	while (arg && *arg)
	{
		++size;
		if (size > MAX_SIZE)
			throw std::out_of_range("Too many args. <= 10 000 is tolerated");
		if (std::string(*arg) == "")
			throw std::runtime_error("bad arguments");
		std::string	token(*arg);
		if (token.find(".", 0) != std::string::npos)
			throw std::runtime_error("bad arguments");
		if (token.find("-", 0) != std::string::npos)
			throw std::runtime_error("bad arguments");
		if (errno == ERANGE)
			throw std::out_of_range("overflow");
		double	val(std::strtod(token.c_str(), &end));
		checkVal(val, end);
		checkDuplicate(vec, val);
		vec.push_back(static_cast<int>(val));
		++arg;
	}
	return vec;
}
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
