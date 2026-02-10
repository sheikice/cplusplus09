#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <limits.h>
#include <exception>
#include <algorithm>
#include <sys/time.h>

//TODO: two algos
void	PmergeMe::pMergeMe(char** arg)
{
	std::vector<int>	before = strToIntVector(arg);
	std::vector<int>	after(before);

	int	nbCmp = 0;
	double start = getTime();
	fordJohnSort(after, nbCmp);
	double end = getTime();
	checkSort(after);
	printResult(before, after, nbCmp);
	printTime(after.size(), start, end);
	std::cout << "\n[TotalCmp = " << nbCmp << "]\n";
}

std::vector<int>	PmergeMe::strToIntVector(char **arg)
{
	std::vector<int>	vec;
	char*	end;

	errno = 0;
	while (arg && *arg)
	{
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
		checkDuplicate(vec, static_cast<int>(val));
		vec.push_back(static_cast<int>(val));
		++arg;
	}
	return vec;
}

void	PmergeMe::fordJohnSort(std::vector<int>& unsorted, int& nbCmp)
{
	bool	oddNbr = false;
	int		lastNbr = unsorted.back();

	if (unsorted.size() < 2)
		return ;
	if (unsorted.size() % 2 != 0)
		oddNbr = true;
	std::vector<std::pair<int, int> >	pairs = makePairs(unsorted, nbCmp);
	std::vector<int>	largers;
	for (size_t i = 0; i < pairs.size(); ++i)
		largers.push_back(pairs[i].first);
	fordJohnSort(largers, nbCmp);
	sortPairs(pairs, largers);

	std::vector<int>	mainChain;
	std::vector<int>	pending;
	mainChain.push_back(pairs[0].second);
	for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); it++)
	{
		mainChain.push_back(it->first);
		pending.push_back(it->second);
	}
	if (oddNbr)
		pending.push_back(lastNbr);
	pendantInsertion(mainChain, pending, pairs, nbCmp);

	unsorted = mainChain;
}

std::vector<std::pair<int, int> >	PmergeMe::makePairs(const std::vector<int>& unsorted, int& nbCmp)
{
	std::vector<std::pair<int, int> >	pairs;

	for (size_t i = 0; i + 1 < unsorted.size(); i += 2)
	{
		++nbCmp;
	  std::cout << "cmp(" << unsorted[i] << "," << unsorted[i + 1] << ")\n";
		if (unsorted[i] > unsorted[i + 1])
			pairs.push_back(std::make_pair(unsorted[i], unsorted[i + 1]));
		else
			pairs.push_back(std::make_pair(unsorted[i + 1], unsorted[i]));
	}
	return pairs;
}

void	PmergeMe::sortPairs(std::vector<std::pair<int, int> >& pairs, const std::vector<int>& largers)
{
	std::vector<std::pair<int, int> >	sorted;

	for (std::vector<int>::const_iterator it1 = largers.begin(); it1 != largers.end(); ++it1)
	{
		for (std::vector<std::pair<int, int> >::const_iterator it2 = pairs.begin(); it2 != pairs.end(); ++it2)
		{
			if (*it1 == it2->first)
			{
				sorted.push_back(*it2);
				break ;
			}
		}
	}
	pairs = sorted;
}

void	PmergeMe::pendantInsertion(std::vector<int>& mainChain, const std::vector<int>& pending, const std::vector<std::pair<int, int> >& pairs, int& nbCmp)
{
	for (size_t i = 1; i < pending.size(); ++i)
	{
		if (isJacobStahlNbr(i + 1) == true || i + 1 == pending.size())
		{
			size_t j = i;
			do
			{
				std::vector<int>::iterator	posAj = std::find(mainChain.begin() + i, mainChain.end(), pairs[j].first);
				if (posAj == mainChain.end())
					binaryInsertion(mainChain, pending[j], mainChain.size(), nbCmp);
				else
					binaryInsertion(mainChain, pending[j],  posAj - mainChain.begin(), nbCmp);
				--j;
			}
			while (isJacobStahlNbr(j + 1) == false);
		}
	}
}

void	PmergeMe::binaryInsertion(std::vector<int>& mainChain, int val, size_t indexMax, int& nbCmp)
{
	std::vector<int>::iterator	last = mainChain.begin() + indexMax;
	std::vector<int>::iterator	it = lowerBound(mainChain.begin(), last, val, nbCmp);

	mainChain.insert(it, val);
}

bool	PmergeMe::isJacobStahlNbr(int nbr)
{
	const int SIZE_JACOBSTAHL_LIST = 13;
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
void	PmergeMe::checkDuplicate(const std::vector<int>& vec, int val)
{
	for (size_t i = 0; i < vec.size(); ++i)
		if (vec[i] == val)
			throw std::runtime_error("duplicate value in arguments");
}

void	PmergeMe::printResult(const std::vector<int>& before, const std::vector<int>& after, const int& nbCmp)
{
	std::cout << "\nBefore: ";
	for (size_t i = 0; i < before.size(); ++i)
		std::cout << " " << before[i];
	std::cout << "\nAfter: ";
	for (size_t i = 0; i < after.size(); ++i)
		std::cout << " " << after[i];
	std::cout << "\n\nTotal nbr of comparisons = " << nbCmp << '\n';
	std::cout << '\n';
}

void	PmergeMe::checkSort(const std::vector<int>& vec)
{
	for(size_t i = 1; i < vec.size(); ++i)
		if (vec[i] < vec[i - 1])
			throw std::runtime_error("sorting has failed");
}

void PmergeMe::printTime(size_t sizeList, double start, double end)
{
	double diffTime = end - start;

	std::cout << "Time to process a range of " << sizeList << " elements with " << "std::vector<int> : " << static_cast<double>(diffTime) << " μs\n";
}

double PmergeMe::getTime()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return time.tv_sec * 1000000 + time.tv_usec;
}
