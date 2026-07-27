#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other), _target(other._target) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
    if (this != &other)
    {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    AForm::execute(executor);
    std::ofstream ofs((_target + "_shrubbery").c_str());
    if (!ofs.is_open())
        throw std::runtime_error("Could not create file");
    
    ofs << "         ^"         << std::endl;
    ofs << "        / \\"        << std::endl;
    ofs << "       /   \\"       << std::endl;
    ofs << "      /     \\"      << std::endl;
    ofs << "     /       \\"     << std::endl;
    ofs << "    /         \\"    << std::endl;
    ofs << "   /           \\"   << std::endl;
    ofs << "  /             \\"  << std::endl;
    ofs << "  ---------------"  << std::endl;
    ofs << "        ||       "  << std::endl;
    ofs << "        ||       "  << std::endl;
    ofs.close();
}
