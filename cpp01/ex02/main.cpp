#include <iostream>
#include <string>

int main(){
    std::string s = "HI THIS IS BRAIN";

    std::string *StringPTR = &s;
    std::string &stringREF = s;

    std::cout << "- address of s: " << &s << std::endl;
    std::cout << "- value of StringPTR: " << StringPTR << std::endl;
    std::cout << "- address of StringREF: " << &stringREF << std::endl;
    std::cout << std::endl;
    
    std::cout << "- string content: " << s << std::endl;
    std::cout << "- StringPTR points to: " << *StringPTR << std::endl;
    std::cout << "- StringREF points to: " << stringREF << std::endl;

    return 0;
}