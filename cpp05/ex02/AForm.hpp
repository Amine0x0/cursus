#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm
{
    public:
        class GradeTooHighException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class GradeTooLowException : public std::exception
        {
            public:
                virtual const char* what() const throw();
        };

        class FormNotSignedException : public std::exception 
        {
            public:
                virtual const char* what() const throw();
        };

        AForm();
        AForm(const std::string& name, int signGrade, int execGrade);
        AForm(const AForm& other);
        AForm& operator=(const AForm& other);
        virtual ~AForm();

        const std::string& getName() const;
        bool getSigned() const;
        int getSignGrade() const;
        int getExecGrade() const;

        void beSigned(const Bureaucrat& b);

        virtual void execute(Bureaucrat const & executor) const = 0;
    private:
        const std::string _name;
        bool _signed;
        const int _signGrade;
        const int _execGrade;
};

std::ostream& operator<<(std::ostream& os, const AForm& f);

#endif