#include "AForm.hpp"
#include "Bureaucrat.hpp"

const char* AForm::FormNotSignedException::what() const throw() 
{
    return "Form not signed";
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return "Grade too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "Grade too low";
}

AForm::AForm() : _name("Default"), _signed(false), _signGrade(150), _execGrade(150) {}

AForm::AForm(const std::string& name, int signGrade, int execGrade) 
    : _name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw AForm::GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm& other) 
    : _name(other._name), _signed(other._signed), _signGrade(other._signGrade), _execGrade(other._execGrade) {}

AForm& AForm::operator=(const AForm& other)
{
    if (this != &other)
        _signed = other._signed;
    return *this;
}

AForm::~AForm() {}

const std::string& AForm::getName() const { return _name; }

bool AForm::getSigned() const { return _signed; }

int AForm::getSignGrade() const { return _signGrade; }

int AForm::getExecGrade() const { return _execGrade; }

void AForm::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _signGrade)
        throw AForm::GradeTooLowException();
    _signed = true;
}

void AForm::execute(Bureaucrat const & executor) const {
    if (!this->getSigned())
        throw AForm::FormNotSignedException();
    if (executor.getGrade() > this->getExecGrade())
        throw AForm::GradeTooLowException();
}

std::ostream& operator<<(std::ostream& os, const AForm& f)
{
    os << "AForm " << f.getName() << " | Signed: " << (f.getSigned() ? "Yes" : "No") 
       << " | Sign Grade: " << f.getSignGrade() << " | Exec Grade: " << f.getExecGrade();
    return os;
}