#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN& other) : s(other.s) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        s = other.s;
    }
    return *this;
}

bool RPN::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool RPN::isNumber(const std::string& token) {
    if (token.length() != 1) return false;
    return std::isdigit(token[0]);
}

int RPN::calculate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                std::cerr << "Error" << std::endl;
                std::exit(1);
            }
            return a / b;
        default: return 0;
    }
}

void RPN::process(const std::string& expression) {
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (isNumber(token)) {
            s.push(token[0] - '0');
        } else if (isOperator(token)) {
            if (s.size() < 2) {
                std::cerr << "Error" << std::endl;
                std::exit(1);
            }
            int b = s.top();
            s.pop();
            int a = s.top();
            s.pop();

            int result = calculate(a, b, token[0]);
            s.push(result);
        } else {
            std::cerr << "Error" << std::endl;
            std::exit(1);
        }
    }

    if (s.size() != 1) {
        std::cerr << "Error" << std::endl;
        std::exit(1);
    }

    std::cout << s.top() << std::endl;
}