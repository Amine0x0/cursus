#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main()
{
    {
        MutantStack<int, std::list<int> > list_stack;
        
        list_stack.push(10);
        list_stack.push(20);
        list_stack.push(30);

        MutantStack<int, std::list<int> >::iterator it = list_stack.begin();
        MutantStack<int, std::list<int> >::iterator ite = list_stack.end();

        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
    }

    {
        MutantStack<int> mstack;
        mstack.push(1);
        mstack.push(2);
        mstack.push(3);

        const MutantStack<int>& const_ref = mstack;

        MutantStack<int>::const_iterator cit = const_ref.begin();
        MutantStack<int>::const_iterator cite = const_ref.end();

        while (cit != cite)
        {
            std::cout << *cit << std::endl;
            ++cit;
        }
    }

    return 0;
}