#include "Bureaucrat.hpp"
#include "Form.hpp"

static const std::string PurpleColor = "\e[0;35m";
static const std::string DefaultColor = "\e[0;37m";

static void sep(std::string context){
    std::cout << PurpleColor 
    << "----------------"
    << context
    << "----------------"
    << DefaultColor
    << std::endl;
}

enum TEST_CASES {
    BUREAUCRAT_VALID,
    BUREAUCRAT_INVALID,
    BUREAUCRAT_EDGE,
    FORM_VALID,
    FORM_INVALID,
    FORM_EDGE
};

static void runBureaucratValid() {
    sep("Bureaucrat Valid");
    Bureaucrat b("NormalWorker", 75);
    std::cout << b << std::endl;
}

static void runBureaucratInvalid() {
    sep("Bureaucrat Invalid");
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

static void runBureaucratEdge() {
    sep("Bureaucrat Edge Cases");
    try {
        Bureaucrat top("Top", 1);
        std::cout << "Attempting to increment " << top << std::endl;
        top.incrementGrade();
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
}

static void runFormValid() {
    sep("Form Valid");
    Bureaucrat bob("Bob", 50);
    Form f("TaxForm", 50, 10);
    bob.signForm(f);
    std::cout << f << std::endl;
}

static void runFormInvalid() {
    sep("Form Invalid");
    Bureaucrat bob("Junior", 100);
    Form f("StrictForm", 50, 10);
    bob.signForm(f);
}

static void runFormEdge() {
    sep("Form Edge Cases");
    try {
        Form f("BadForm", 0, 151);
    } catch (std::exception &e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    Bureaucrat exact("Exact", 50);
    Form f2("Boundary", 50, 1);
    exact.signForm(f2);
}

static void test(TEST_CASES c) {
    switch (c) {
        case BUREAUCRAT_VALID:
            runBureaucratValid();
            break;
        case BUREAUCRAT_INVALID:
            runBureaucratInvalid();
            break;
        case BUREAUCRAT_EDGE:
            runBureaucratEdge();
            break;
        case FORM_VALID:
            runFormValid();
            break;
        case FORM_INVALID:
            runFormInvalid();
            break;
        case FORM_EDGE:
            runFormEdge();
            break;
        default:
            std::cout << "Unknown test case." << std::endl;
            break;
    }
}

int main() {
    test(BUREAUCRAT_VALID);
    test(BUREAUCRAT_INVALID);
    test(BUREAUCRAT_EDGE);
    test(FORM_VALID);
    test(FORM_INVALID);
    test(FORM_EDGE);
    return 0;
}