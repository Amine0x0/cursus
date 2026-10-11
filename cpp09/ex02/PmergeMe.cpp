#include "PmergeMe.hpp"


PmergeMe::PmergeMe() : v(), dq(){}

PmergeMe::PmergeMe(PmergeMe const &src) : v(src.v), dq(src.dq){}

PmergeMe	&PmergeMe::operator=(PmergeMe const &other)
{
	if (this != &other)
	{
		v = other.v;
		dq = other.dq;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{
}

char const	*PmergeMe::BadInputException::what() const throw()
{
	return ("Error");
}


void	PmergeMe::parseArgs(int argc, char **argv)
{
	if (argc < 2)
		throw BadInputException();
	for (int i = 1; i < argc; i++)
	{
		std::string	token(argv[i]);

		if (token.empty())
			throw BadInputException();
		for (size_t j = 0; j < token.length(); j++)
			if (!std::isdigit(token[j]))
				throw BadInputException();

		long	value = std::strtol(token.c_str(), NULL, 10);
		if (value > std::numeric_limits<int>::max())
			throw BadInputException();

		v.push_back(static_cast<int>(value));
		dq.push_back(static_cast<int>(value));
	}
}


long	PmergeMe::jacobsthal(long n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (jacobsthal(n - 1) + 2 * jacobsthal(n - 2));
}

void	PmergeMe::binaryInsertVec(std::vector<int> &chain, int value, int limit)
{
	int lo = 0, hi = limit;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
        value < chain[mid] ? hi = mid : lo = mid + 1;
	}
	chain.insert(chain.begin() + lo, value);
}

std::vector<int>	PmergeMe::fordJohnsonVec(std::vector<int> const &input)
{
	if (input.size() <= 1)
    	return (input);

	std::vector<int>  winners;
	std::vector<int>  losers;
	int               leftover = 0;
	bool              hasLeftover = false;

	size_t  i = 0;
	while (i + 1 < input.size())
	{
	    if (input[i] > input[i + 1])
	    {
	        winners.push_back(input[i]);
	        losers.push_back(input[i + 1]);
	    }
	    else
	    {
	        winners.push_back(input[i + 1]);
	        losers.push_back(input[i]);
	    }
	    i += 2;	
	}
	if (i < input.size())
	{
	    leftover = input[i];
	    hasLeftover = true;
	}

	std::vector<int>  sortedWinners = fordJohnsonVec(winners);
	std::vector<int>  sortedLosers;
	std::vector<bool> used(winners.size(), false);

	for (size_t k = 0; k < sortedWinners.size(); k++)
	{
	    for (size_t j = 0; j < winners.size(); j++)
	    {
	        if (!used[j] && winners[j] == sortedWinners[k])
	        {
	            sortedLosers.push_back(losers[j]);
	            used[j] = true;
	            break;
	        }
	    }
	}

	std::vector<int> chain = sortedWinners;

	chain.insert(chain.begin(), sortedLosers[0]);

	size_t  n = sortedLosers.size();
	size_t  prev = 1;

	for (long k = 3; prev < n; k++)
	{
	    size_t  jt = static_cast<size_t>(jacobsthal(k));
	    if (jt > n){
			jt = n;
		}
		// std::cout << jt << std::endl;
	    for (size_t idx = jt; idx > prev; idx--)
	    {
	        int  value  = sortedLosers[idx - 1];
	        int  winner = sortedWinners[idx - 1];
	        int  limit  = std::lower_bound(chain.begin(), chain.end(), winner)
	                      - chain.begin();
	        binaryInsertVec(chain, value, limit);
	    }
	    prev = jt;
	}
	if (hasLeftover)
    	binaryInsertVec(chain, leftover, chain.size());
	return (chain);
}

void	PmergeMe::binaryInsertDeq(std::deque<int> &chain, int value, int limit)
{
	int lo = 0, hi = limit;
	while (lo < hi) {
		int mid = (lo + hi) / 2;
        value < chain[mid] ? hi = mid : lo = mid + 1;
	}
	chain.insert(chain.begin() + lo, value);
}

std::deque<int>	PmergeMe::fordJohnsonDeq(std::deque<int> const &input)
{
	if (input.size() <= 1)
    	return (input);

	std::deque<int>  winners;
	std::deque<int>  losers;
	int               leftover = 0;
	bool              hasLeftover = false;

	size_t  i = 0;
	while (i + 1 < input.size())
	{
	    if (input[i] > input[i + 1])
	    {
	        winners.push_back(input[i]);
	        losers.push_back(input[i + 1]);
	    }
	    else
	    {
	        winners.push_back(input[i + 1]);
	        losers.push_back(input[i]);
	    }
	    i += 2;
	}
	if (i < input.size())
	{
	    leftover = input[i];
	    hasLeftover = true;
	}

	std::deque<int>  sortedWinners = fordJohnsonDeq(winners);
	std::deque<int>  sortedLosers;
	std::deque<bool> used(winners.size(), false);

	for (size_t k = 0; k < sortedWinners.size(); k++)
	{
	    for (size_t j = 0; j < winners.size(); j++)
	    {
	        if (!used[j] && winners[j] == sortedWinners[k])
	        {
	            sortedLosers.push_back(losers[j]);
	            used[j] = true;
	            break;
	        }
	    }
	}

	std::deque<int> chain = sortedWinners;

	chain.insert(chain.begin(), sortedLosers[0]);

	size_t  n = sortedLosers.size();
	size_t  prev = 1;

	for (long k = 3; prev < n; k++)
	{
	    size_t  jt = static_cast<size_t>(jacobsthal(k));
	    if (jt > n)
	        jt = n;

	    for (size_t idx = jt; idx > prev; idx--)
	    {
	        int  value  = sortedLosers[idx - 1];
	        int  winner = sortedWinners[idx - 1];
	        int  limit  = std::lower_bound(chain.begin(), chain.end(), winner)
	                      - chain.begin();
	        binaryInsertDeq(chain, value, limit);
	    }
	    prev = jt;
	}
	if (hasLeftover)
    	binaryInsertDeq(chain, leftover, chain.size());
	return (chain);
}


void	PmergeMe::run()
{
	std::cout << "Before:";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << " " << v[i];
	std::cout << std::endl;

	std::clock_t		startV = std::clock();
	std::vector<int>	sortedV = fordJohnsonVec(v);
	std::clock_t		endV = std::clock();

	std::clock_t		startD = std::clock();
	std::deque<int>		sortedD = fordJohnsonDeq(dq);
	std::clock_t		endD = std::clock();

	if (sortedV.size() != sortedD.size()
		|| !std::equal(sortedV.begin(), sortedV.end(), sortedD.begin()))
		std::cerr << "no match" << std::endl;

	std::cout << "After: ";
	for (size_t i = 0; i < sortedV.size(); i++)
		std::cout << " " << sortedV[i];
	std::cout << std::endl;

	double	VectorTime = 1000000.0 * (endV - startV) / CLOCKS_PER_SEC;
	double	DeqeueTime = 1000000.0 * (endD - startD) / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << v.size()
			  << " elements with std::vector : " << VectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << dq.size()
			  << " elements with std::deque : " << DeqeueTime << " us" << std::endl;
}