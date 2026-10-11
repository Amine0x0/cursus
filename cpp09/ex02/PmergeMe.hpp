#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
# include <vector>
# include <deque>
# include <string>
# include <exception>

class PmergeMe
{
	private:
		std::vector<int>	v;
		std::deque<int>		dq;

		std::vector<int>	fordJohnsonVec(std::vector<int> const &input);
		void				binaryInsertVec(std::vector<int> &chain,
											int value, int limit);

		std::deque<int>		fordJohnsonDeq(std::deque<int> const &input);
		void				binaryInsertDeq(std::deque<int> &chain,
											int value, int limit);

		static long			jacobsthal(long n);

	public:
		PmergeMe();
		PmergeMe(PmergeMe const &src);
		PmergeMe	&operator=(PmergeMe const &rhs);
		~PmergeMe();

		void	parseArgs(int argc, char **argv);

		void	run();

		class BadInputException : public std::exception
		{
			public:
				virtual char const	*what() const throw();
		};
};

#endif