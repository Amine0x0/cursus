#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
	public:
		typedef typename Container::iterator		iterator;
		typedef typename Container::const_iterator	const_iterator;


		MutantStack() : std::stack<T, Container>() {}

		MutantStack(MutantStack const &src) : std::stack<T, Container>(src) {}

		MutantStack	&operator=(MutantStack const &rhs)
		{
			if (this != &rhs)
				std::stack<T, Container>::operator=(rhs);
			return (*this);
		}

		virtual ~MutantStack() {}

		iterator begin() { return this->c.begin(); }
		iterator end() { return this->c.end(); }
		const_iterator begin() const { return this->c.begin(); }
		const_iterator end() const { return this->c.end(); }
};

#endif