#include "PmergeMe.hpp"
#include <sstream>
#include <cstdlib>

//TODO: two algos
void	PmergeMe::pMergeMe(const char* arg)
{
	bool	oddNbr = false;
	std::vector<int> nbrs = strToIntVector(arg);
	FordJohnSort(nbrs);
}

//TODO: parse arg in vector<int>
std::vector<int> PmergeMe::strToIntVector(const char *arg)
{
	std::vector<int> vec;
	std::istringstream is(arg);
	std::string token;
	char* ptr;

	while (is >> token)
		vec.push_back(std::strtof(token.c_str(), &ptr));
	return vec;
}

std::vector<int> PmergeMe::FordJohnSort(const std::vector<int>& unsorted)
{
	bool	oddNbr = false;
	int		lastNbr = unsorted.back();

	if (unsorted.size() < 2)
		return unsorted;
	if (unsorted.size() % 2 != 0)
		oddNbr = true;
	std::vector<std::pair<int, int> > pairs = makeSortedPairs(unsorted);
	mergeInsert(pairs);
	std::vector<int> mainChain;
	std::vector<int> pendantChain;
	mainChain.push_back(pairs[0].second);
	for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); it++)
		mainChain.push_back(it->first);
	pendantInsertion(mainChain, pairs);
	if (oddNbr)
		binaryInsertion(mainChain, lastNbr);
	return mainChain;
}

std::vector<std::pair<int, int> > PmergeMe::makeSortedPairs(const std::vector<int>& unsorted)
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

std::vector<std::pair<int, int> > PmergeMe::makeSortedPairs(const std::vector<std::pair<int, int>>& unsorted)
{
	std::vector<std::pair<int, int> > pairs;

	for (size_t i = 0; i + 1 < unsorted.size(); i += 2)
	{
		if (unsorted[i] > unsorted[i + 1])
			pairs.push_back(std::make_pair(i, i + 1));
		else
			pairs.push_back(std::make_pair(i + 1, i));
	}
	return pairs;
}

void	PmergeMe::mergeInsert(std::vector<std::pair<int, int> >& pairs)
{
	bool	oddNbr = false;
	std::pair<int, int> lastPair = pairs.back();

	if (pairs.size() < 2)
		return ;
	if (pairs.size() % 2 != 0)
		oddNbr = true;
	std::vector<std::pair<int, int> > indexPairs = makeSortedPairs(pairs);
	mergeInsert(indexPairs);
	std::vector<std::pair<int, int> > mainChain;

	mainChain.push_back(pairs[indexPairs[0].second]);
	for (size_t i = 0; i < indexPairs.size(); i++)
		mainChain.push_back(pairs[indexPairs[i].first]);
	//TODO: SORT
	pendantInsertion(mainChain, indexPairs);
	if (oddNbr == true)
	{
		binaryInsertion(mainChain, lastPair.first);
		binaryInsertion(mainChain, lastPair.second);
	}
	pairs = mainChain;
}

void PmergeMe::pendantInsertion(std::vector<int>& mainChain, std::vector<std::pair<int, int> > pairs)
{
	for (size_t i = 3; i < pairs.size(); i++)
	{
		if (isJacobStahlNbr(i) == true)
		{
			size_t j = i;
			binaryInsertion(mainChain, pairs[j].second);
			j--;
			while (isJacobStahlNbr(j) == false)
			{
				binaryInsertion(mainChain, pairs[j].second);
				j--;
			}
		}
	}
}

void PmergeMe::pendantInsertion(std::vector<std::pair<int, int> >& mainChain, std::vector<std::pair<int, int> > pairs)
{
	for (size_t i = 3; i < pairs.size(); i++)
	{
		if (isJacobStahlNbr(i) == true)
		{
			size_t j = i;
			binaryInsertion(mainChain, pairs[j].second);
			j--;
			while (isJacobStahlNbr(j) == false)
			{
				binaryInsertion(mainChain, pairs[j].second);
				j--;
			}
		}
	}
}

void PmergeMe::binaryInsertion(std::vector<int>& mainChain, int nbr)
{
	size_t indexMin = 0;
	size_t indexMax = mainChain.size() - 1;
	while (indexMin < indexMax)
	{
		size_t indexMid = indexMin + (indexMin - indexMax) / 2;
		if (nbr < mainChain[indexMid])
			indexMax = indexMid;
		else
			indexMin = indexMid;
	}
	mainChain.insert(mainChain.begin() + indexMin, nbr);
}

void PmergeMe::binaryInsertion(std::vector<std::pair<int, int> >& mainChain, int nbr)
{
	size_t indexMin = 0;
	size_t indexMax = mainChain.size() - 1;
	while (indexMin < indexMax)
	{
		size_t indexMid = indexMin + (indexMin - indexMax) / 2;
		if (nbr < mainChain[indexMid])
			indexMax = indexMid;
		else
			indexMin = indexMid;
	}
	mainChain.insert(mainChain.begin() + indexMin, nbr);
}

//TODO: Check if nbr list of Jacob is correct
bool PmergeMe::isJacobStahlNbr(int nbr)
{
	std::vector<int> JacobNbr = {1, 3, 5, 11, 21, 43,85, 171, 341, 683, 1365, 2731, 5461};

	for (size_t i = 0; i < JacobNbr.size(); i++)
		if (nbr == JacobNbr[i])
			return true;
	return false;
}
