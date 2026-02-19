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
		static void	checkVal(double, char*);
		static bool	isJacobStahlNbr(int);
		static double	getTime();
		static void	printTime(std::size_t, double, double, const std::string&);

		template <typename T1, typename T2>
		static void	pMergeMe(char** arg, std::string type)
		{
			double	start = getTime();
			T1	before;
			strConvert(arg, before);
			T1	after(before);

			int	nbCmp = 0;
			fordJohnSort<T1, T2>(after, nbCmp);
			double	end = getTime();

			checkSort(after);
			if (type == "vector")
				printResult(before, after, nbCmp);
			printTime(after.size(), start, end, type);
		}

		template<typename T>
		static T	strConvert(char **arg, T& container)
		{
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
				checkDuplicate(container, val);
				container.push_back(static_cast<int>(val));
				++arg;
			}
			return container;
		}

		template<typename T>
		static void	binaryInsertion(T& mainChain, int val, size_t indexMax, int& nbCmp)
		{
			typename T::iterator	last = mainChain.begin() + indexMax;
			typename T::iterator	it = lowerBound(mainChain.begin(), last, val, nbCmp);

			mainChain.insert(it, val);
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
			T1	largers;
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
						if (j > pairs.size())
								binaryInsertion(mainChain, pending[j], mainChain.size(), nbCmp);
						else
						{
							typename T1::iterator	posAj = std::find(mainChain.begin() + i, mainChain.end(), pending[j]);
							binaryInsertion(mainChain, pending[j],  posAj - mainChain.begin(), nbCmp);
						}
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
			std::cout << "\n\nTotal nbr of comparisons = " << nbCmp << "\n\n";
			std::cout << "Before: ";
			for (size_t i = 0; i < before.size(); ++i)
				std::cout << " " << before[i];
			std::cout << "\nAfter: ";
			for (size_t i = 0; i < after.size(); ++i)
				std::cout << " " << after[i];
			std::cout << '\n';
		}

		template<typename T>
		static void	checkSort(const T& cont)
		{
			for(size_t i = 1; i < cont.size(); ++i)
				if (cont[i] < cont[i - 1])
					throw std::runtime_error("sorting has failed");
		}

		template <typename T>
		static void	checkDuplicate(const T& cont, int val)
		{
			for (size_t i = 0; i < cont.size(); ++i)
				if (cont[i] == val)
					throw std::runtime_error("duplicate value in arguments");
		}
};
#endif
