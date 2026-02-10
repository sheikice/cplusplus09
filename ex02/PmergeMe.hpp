#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <cstdlib>

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
		static void	checkDuplicate(const std::vector<int>&, int);

		static void	fordJohnSort(std::vector<int>&, int&);
		static std::vector<std::pair<int, int> >	makePairs(const std::vector<int>&, int&);
		static void	sortPairs(std::vector<std::pair<int, int> >&, const std::vector<int>&);
		static void	pendantInsertion(std::vector<int>&, const std::vector<int>&, const std::vector<std::pair<int, int> >&, int&);
		static void	binaryInsertion(std::vector<int>&, int, std::size_t, int&);
		static bool	isJacobStahlNbr(int);

		static void	printResult(const std::vector<int>&, const std::vector<int>&, const int&);
		static void	checkSort(const std::vector<int>&);

		static double	getTime();
		static void	printTime(std::size_t, double start, double end);
};

template<typename ForwardIterator>
ForwardIterator	lowerBound(ForwardIterator first, ForwardIterator last, int val, int& nbComp)
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
		std::cout << "cmp(" << val << "," <<  *middle << ")\n";
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

#endif
