#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>

class PmergeMe
{
	private:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe& operator=(const PmergeMe&);

	public:
		static void pMergeMe(char**);
		static std::vector<int> strToIntVector(char**);
		static void fordJohnSort(std::vector<int>&);
		static std::vector<std::pair<int, int> > makePairs(const std::vector<int>&);
		static void sortPairs(std::vector<std::pair<int, int> >&, const std::vector<int>&);
		static void binaryInsertion(std::vector<int>&, int, std::size_t);
		static void pendantInsertion(std::vector<int>&, const std::vector<std::pair<int, int> >&);
		static bool isJacobStahlNbr(int);
		static void checkVal(double, char*);
		static void checkDuplicate(const std::vector<int>&, int);
		static void printResult(const std::vector<int>&, const std::vector<int>&);
		static void checkSort(const std::vector<int>&);
};

#endif
