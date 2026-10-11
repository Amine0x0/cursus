#include "Iter.hpp"
#include <cctype>
#include <string>

void half(int &number){
    number /= 2;
}

void rot13(std::string &str) {
    for (size_t i = 0; i < str.size(); i++) {
        if (std::isalpha(str[i])) {
            char base = std::isupper(str[i]) ? 'A' : 'a';
            str[i] = base + (str[i] - base + 13) % 26;
        }
    }
}

int main(){
    int nums[] = {10,20,30,40,50};

    ::iter(nums, 5, half);
    for (int i = 0; i < 5; i++)
        std::cout << nums[i] << std::endl;
    std::cout << "----------------" << std::endl;
    std::string test[] = {"bruh", "idk", "check"};
    std::cout << "before:" << std::endl;    
	for (int i = 0; i < 3; i++)
		std::cout << "[" << test[i] << "]" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "after:" << std::endl; 
    ::iter(test, 3, rot13);
	for (int i = 0; i < 3; i++)
		std::cout << "[" << test[i] << "]" << std::endl;

    return 0;
}