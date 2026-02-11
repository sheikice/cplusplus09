#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <limits.h>
#include <exception>
#include <algorithm>
#include <sys/time.h>

class PmergeMe
{
	private:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe&	operator=(const PmergeMe&);

	public:
		static void	pMergeMe(char**);
		static std::vector<int>	strToIntVector(char**);
		static void	checkVal(double, char*);

		static bool	isJacobStahlNbr(int);

		static double	getTime();
		static void	printTime(std::size_t, double start, double end);

		template<typename T>
		static void	binaryInsertion(T& mainChain, int val, size_t indexMax, int& nbCmp)
		{
			typename T::iterator	last = mainChain.begin() + indexMax;
			typename T::iterator	it = lowerBound(mainChain.begin(), last, val, nbCmp);

			mainChain.insert(it, val);
		}

		//Insert pending chain in main chain
		template<typename T1, typename T2>
		static void	pendingInsertion(T1& mainChain, const T1& pending, const T2& pairs, int& nbCmp)
		{
			for (size_t i = 1; i < pending.size(); ++i)
			{
				if (isJacobStahlNbr(i + 1) == true || i + 1 == pending.size())
				{
					size_t j = i;
					do
					{
						typename T1::iterator	posAj = std::find(mainChain.begin() + i, mainChain.end(), pairs[j].first);
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

		template<typename ForwardIterator>
		static ForwardIterator	lowerBound(ForwardIterator first, ForwardIterator last, int val, int& nbComp)
		{
			typedef typename std::iterator_traits<ForwardIterator>::difference_type DistanceType;
			DistanceType len = last - first;

			while (len > 0)
			{
				DistanceType half = len >> 1;
				ForwardIterator middle = first;
				for (DistanceType i = 0; i < half; ++i)
					++middle;
				++nbComp;
				if (val > *middle)
				{
					first = middle;
					++first;
					len = len - half - 1;
				}
				else
				len = half;
			}
			return first;
		}

		template<typename T>
		static void	printResult(const T& before, const T& after, const int& nbCmp)
		{
			std::cout << "\nBefore: ";
			for (size_t i = 0; i < before.size(); ++i)
				std::cout << " " << before[i];
			std::cout << "\nAfter: ";
			for (size_t i = 0; i < after.size(); ++i)
				std::cout << " " << after[i];
			std::cout << "\n\nTotal nbr of comparisons = " << nbCmp << "\n\n";
		}

		template<typename T>
		static void	checkSort(const T& vec)
		{
			for(size_t i = 1; i < vec.size(); ++i)
				if (vec[i] < vec[i - 1])
					throw std::runtime_error("sorting has failed");
		}

		template <typename T>
		static void	checkDuplicate(const T& vec, int val)
	{
		for (size_t i = 0; i < vec.size(); ++i)
			if (vec[i] == val)
				throw std::runtime_error("duplicate value in arguments");
	}

		template <typename T1, typename T2>
		static void	fordJohnSort(T1& unsorted, int& nbCmp)
		{
			bool	oddNbr = false;
			int		lastNbr = unsorted.back();

			if (unsorted.size() < 2)
				return ;
			if (unsorted.size() % 2 != 0)
				oddNbr = true;
			T2	pairs = makePairs<T1, T2>(unsorted, nbCmp);
			T1 largers;
			for (size_t i = 0; i < pairs.size(); ++i)
				largers.push_back(pairs[i].first);
			fordJohnSort<T1, T2>(largers, nbCmp);
			sortPairs(pairs, largers);

			T1	mainChain;
			T1	pending;
			mainChain.push_back(pairs[0].second);
			for (typename T2::const_iterator it = pairs.begin(); it != pairs.end(); it++)
			{
				mainChain.push_back(it->first);
				pending.push_back(it->second);
			}
			if (oddNbr)
				pending.push_back(lastNbr);
			pendingInsertion(mainChain, pending, pairs, nbCmp);

			unsorted = mainChain;
		}

		template <typename T1, typename T2>
		static T2	makePairs(const T1& unsorted, int& nbCmp)
		{
			T2	pairs;

			for (size_t i = 0; i + 1 < unsorted.size(); i += 2)
			{
				++nbCmp;
				if (unsorted[i] > unsorted[i + 1])
					pairs.push_back(std::make_pair(unsorted[i], unsorted[i + 1]));
				else
					pairs.push_back(std::make_pair(unsorted[i + 1], unsorted[i]));
			}
			return pairs;
		}

		template <typename T1, typename T2>
		static void	sortPairs(T2& pairs, const T1& largers)
		{
			T2	sorted;

			for (typename T1::const_iterator it1 = largers.begin(); it1 != largers.end(); ++it1)
			{
				for (typename T2::const_iterator it2 = pairs.begin(); it2 != pairs.end(); ++it2)
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

};
#endif
