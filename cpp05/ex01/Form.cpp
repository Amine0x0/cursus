#include "Form.hpp"
#include "Bureaucrat.hpp"
const char* Form::GradeTooHighException::what() const throw()
{
    return "Grade too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Grade too low";
}

Form::Form() : _name("Default"), _signed(false), _signGrade(150), _execGrade(150) {}

Form::Form(const std::string& name, int signGrade, int execGrade) 
    : _name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw Form::GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw Form::GradeTooLowException();
}

Form::Form(const Form& other) 
    : _name(other._name), _signed(other._signed), _signGrade(other._signGrade), _execGrade(other._execGrade) {}

Form& Form::operator=(const Form& other)
{
    if (this != &other)
        _signed = other._signed;
    return *this;
}

Form::~Form() {}

const std::string& Form::getName() const { return _name; }

bool Form::getSigned() const { return _signed; }

int Form::getSignGrade() const { return _signGrade; }

int Form::getExecGrade() const { return _execGrade; }

void Form::beSigned(const Bureaucrat& b)
{
    if (b.getGrade() > _signGrade)
        throw Form::GradeTooLowException();
    _signed = true;
}

std::ostream& operator<<(std::ostream& os, const Form& f)
{
    os << "Form " << f.getName() << " | Signed: " << (f.getSigned() ? "Yes" : "No") 
       << " | Sign Grade: " << f.getSignGrade() << " | Exec Grade: " << f.getExecGrade();
    return os;
}