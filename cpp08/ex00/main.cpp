#include "easyfind.hpp"
#include <vector>

int main(){
    {
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        try {
            std::vector<int>::iterator it = ::easyfind(v, 1);
            std::cout << *it << std::endl;
        }
        catch(NotFoundExcept& e){
            std::cerr << e.what() << std::endl;
        }
    }

    {
        std::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);
        v.push_back(4);
        try {
            std::vector<int>::iterator it = ::easyfind(v, 0);
            std::cout << *it << std::endl;
        }
        catch(NotFoundExcept& e){
            std::cerr << e.what() << std::endl;
        }
    }   
    return 0;
}