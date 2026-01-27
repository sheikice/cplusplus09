#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>

class PmergeMe
{
	private:
		PmergeMe();
		~PmergeMe();

	public:
		static void pMergeMe(const char*);
		static std::vector<int> strToIntVector(const char*);
		static std::vector<int> FordJohnSort(const std::vector<int>&);
		static void mergeInsert(std::vector<std::pair<int, int> >&);
		static std::vector<std::pair<int, int> > makeSortedPairs(const std::vector<int>&);
		static std::vector<std::pair<int, int> > makeSortedPairs(const std::vector<std::pair<int, int>>&);
		static void binaryInsertion(std::vector<int>&, int);
		static void binaryInsertion(std::vector<std::pair<int, int> >&, int);
		static void pendantInsertion(std::vector<int>&, std::vector<std::pair<int, int> >);
		static void pendantInsertion(std::vector<std::pair<int, int> >&, std::vector<std::pair<int, int> >);
		static bool isJacobStahlNbr(int);
};

#endif
