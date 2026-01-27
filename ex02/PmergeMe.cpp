#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <limits.h>
#include <exception>
#include <algorithm>

//TODO: two algos
void	PmergeMe::pMergeMe(char** arg)
{
	std::vector<int> before = strToIntVector(arg);
	std::vector<int> after(before);
	fordJohnSort(after);
	checkSort(after);
	printResult(before, after);
}

std::vector<int> PmergeMe::strToIntVector(char **arg)
{
	std::vector<int> vec;
	char* end;
	errno = 0;

	while (arg && *arg)
	{
		std::string token(*arg);
		if (token.find(".", 0) != std::string::npos)
			throw std::runtime_error("bad arguments");
		if (token.find("-", 0) != std::string::npos)
			throw std::runtime_error("bad arguments");
		if (errno == ERANGE)
			throw std::out_of_range("overflow");
		double val(std::strtod(token.c_str(), &end));
		checkVal(val, end);
		checkDuplicate(vec, static_cast<int>(val));
		vec.push_back(static_cast<int>(val));
		arg++;
	}
	return vec;
}

void PmergeMe::fordJohnSort(std::vector<int>& unsorted)
{
	bool	oddNbr = false;
	int		lastNbr = unsorted.back();

	if (unsorted.size() < 2)
		return ;
	if (unsorted.size() % 2 != 0)
		oddNbr = true;
	std::vector<std::pair<int, int> > pairs = makePairs(unsorted);
	std::vector<int> largers;
	for (size_t i = 0; i < pairs.size(); i++)
		largers.push_back(pairs[i].first);
	fordJohnSort(largers);
	sortPairs(pairs, largers);

	std::vector<int> mainChain;
	mainChain.push_back(pairs[0].second);
	for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); it++)
		mainChain.push_back(it->first);
	pendantInsertion(mainChain, pairs);

	if (oddNbr)
		binaryInsertion(mainChain, lastNbr, mainChain.size());
	unsorted = mainChain;
}

std::vector<std::pair<int, int> > PmergeMe::makePairs(const std::vector<int>& unsorted)
{
	std::vector<std::pair<int, int> > pairs;

	for (size_t i = 0; i + 1 < unsorted.size(); i += 2)
	{
		if (unsorted[i] > unsorted[i + 1])
			pairs.push_back(std::make_pair(unsorted[i], unsorted[i + 1]));
		else
			pairs.push_back(std::make_pair(unsorted[i + 1], unsorted[i]));
	}
	return pairs;
}

void PmergeMe::sortPairs(std::vector<std::pair<int, int> >& pairs, const std::vector<int>& largers)
{
	std::vector<std::pair<int, int> > sorted;

	for (std::vector<int>::const_iterator it1 = largers.begin(); it1 != largers.end(); it1++)
	{
		for (std::vector<std::pair<int, int> >::const_iterator it2 = pairs.begin(); it2 != pairs.end(); it2++)
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

void PmergeMe::pendantInsertion(std::vector<int>& mainChain, const std::vector<std::pair<int, int> >& pairs)
{
	for (size_t i = 1; i < pairs.size(); i++)
	{
		if (isJacobStahlNbr(i + 1) == true || i + 1 == pairs.size())
		{
			size_t j = i;
			do
			{
				std::vector<int>::iterator	posAj = std::find(mainChain.begin() + i, mainChain.end(), pairs[j].first);
				binaryInsertion(mainChain, pairs[j].second,  posAj - (mainChain.begin()));
				j--;
			}
			while (isJacobStahlNbr(j + 1) == false);
		}
	}
}

void PmergeMe::binaryInsertion(std::vector<int>& mainChain, int nbr, size_t indexMax)
{
	std::vector<int>::iterator last = mainChain.begin() + indexMax;
	std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), last, nbr);

	mainChain.insert(it, nbr);
}

bool PmergeMe::isJacobStahlNbr(int nbr)
{
	int JacobNbr[13] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};

	for (size_t i = 0; i < 13; i++)
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
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (vec[i] == val)
			throw std::runtime_error("duplicate value in arguments");
	}
}

void PmergeMe::printResult(const std::vector<int>& before, const std::vector<int>& after)
{
	std::cout << "Before: ";
	for (size_t i = 0; i < before.size(); i++)
		std::cout << " " << before[i];
	std::cout << "\nAfter: ";
	for (size_t i = 0; i < after.size(); i++)
		std::cout << " " << after[i];
	std::cout << '\n';
}

void	PmergeMe::checkSort(const std::vector<int>& vec)
{
	for(size_t i = 1; i < vec.size(); i++)
	{
		std::cout << " " << vec[i];
		if (vec[i] < vec[i - 1])
			throw std::runtime_error("sorting has failed");
	}
	std::cout << '\n';
}
