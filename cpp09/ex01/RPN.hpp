#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <cctype>

class RPN{
    private:
        std::stack<int> s;
        bool isOperator(const std::string& token);
        bool isNumber(const std::string& token);
        int calculate(int a, int b, char op);

    public:
        RPN();
        ~RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);

        void process(const std::string& expression);
};

#endif