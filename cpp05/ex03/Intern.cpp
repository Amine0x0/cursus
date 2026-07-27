#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}
Intern::Intern(const Intern& other) { (void)other; }
Intern& Intern::operator=(const Intern& other) { (void)other; return *this; }
Intern::~Intern() {}

Intern::FormType Intern::getFormType(const std::string& formName) const {
    std::string names[] = {"shrubbery creation", "robotomy request", "presidential pardon"};
    for (int i = 0; i < 3; i++) {
        if (formName == names[i])
            return static_cast<FormType>(i);
    }
    return UNKNOWN;
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) {
    switch (getFormType(formName)) {
        case SHRUBBERY:
            std::cout << "Intern creates ShrubberyCreationForm" << std::endl;
            return new ShrubberyCreationForm(target);
        case ROBOTOMY:
            std::cout << "Intern creates RobotomyRequestForm" << std::endl;
            return new RobotomyRequestForm(target);
        case PARDON:
            std::cout << "Intern creates PresidentialPardonForm" << std::endl;
            return new PresidentialPardonForm(target);
        default:
            std::cout << "Intern cannot create " << formName << " because it does not exist." << std::endl;
            return NULL;
    }
}