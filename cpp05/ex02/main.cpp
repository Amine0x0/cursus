#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <ctime>
#include <cstdlib>

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
    SHRUBBERY_TEST,
    ROBOTOMY_TEST,
    PARDON_TEST,
    EXECUTION_FAILURE_TEST
};

static void runShrubberyTest() {
    sep("Shrubbery Creation Test");
    Bureaucrat b("Gardener", 100);
    ShrubberyCreationForm f("Test");
    
    b.signForm(f);
    b.executeForm(f);
}

static void runRobotomyTest() {
    sep("Robotomy Request Test");
    Bureaucrat b("Doctor", 40);
    RobotomyRequestForm f("Patient");
    
    b.signForm(f);
    b.executeForm(f);
}

static void runPardonTest() {
    sep("Presidential Pardon Test");
    Bureaucrat b("President", 1);
    PresidentialPardonForm f("Criminal");
    
    b.signForm(f);
    b.executeForm(f);
}

static void runExecutionFailureTest() {
    sep("Execution Failure Test");
    Bureaucrat b("Intern", 150);
    PresidentialPardonForm f("Target");
    b.executeForm(f);    
    b.signForm(f);
    b.executeForm(f);
}

static void test(TEST_CASES c) {
    switch (c) {
        case SHRUBBERY_TEST:         runShrubberyTest();         break;
        case ROBOTOMY_TEST:          runRobotomyTest();          break;
        case PARDON_TEST:            runPardonTest();            break;
        case EXECUTION_FAILURE_TEST: runExecutionFailureTest();  break;
    }
}

int main() {
    std::srand(std::time(NULL));
    test(SHRUBBERY_TEST);
    test(ROBOTOMY_TEST);
    test(PARDON_TEST);
    test(EXECUTION_FAILURE_TEST);
    return 0;
}