#include "Bureaucrat.hpp"

static const std::string PurpleColor = "\e[0;35m";
static const std::string DefaultColor = "\e[0;37m";

enum TEST_CASES {
    VALID,
    INVALID,
    EDGE_CASES
};

static void sep(std::string context){
    std::cout << PurpleColor 
    << "----------------"
    << context
    << "----------------"
    << DefaultColor
    << std::endl;
}

static void runValidTests() {
    sep("valid");
    Bureaucrat b("NormalWorker", 75);
    std::cout << b << std::endl;
    b.incrementGrade();
    std::cout << "After increment: " << b << std::endl;
} 

static void runInvalidTests() {
    sep("invalid");
    try {
        Bureaucrat b("TooLow", 151);
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try {
        Bureaucrat b("TooHigh", 0);
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
}

static void runEdgeCaseTests() {
    sep("edge cases");
    try {
        Bureaucrat top("TopRank", 1);
        std::cout << "Attempting to increment " << top << std::endl;
        top.incrementGrade();
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    try {
        Bureaucrat bottom("BottomRank", 150);
        std::cout << "Attempting to decrement " << bottom << std::endl;
        bottom.decrementGrade();
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
}

static void test(TEST_CASES c) {
    switch (c) {
        case VALID:
            runValidTests();
            break;
        case INVALID:
            runInvalidTests();
            break;
        case EDGE_CASES:
            runEdgeCaseTests();
            break;
        default:
            std::cout << "Unknown test case." << std::endl;
            break;
    }
}

int main() {
    test(VALID);
    test(INVALID);
    test(EDGE_CASES);
    return 0;
}