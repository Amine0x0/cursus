#include "../../include/Header.hpp"

const std::string MSG = "PhoneBook v.0";

void	ConsoleUI::print(std::string input)
{
	if (input.empty())
		return ;

	std::cout << input << std::endl;
}

void	ConsoleUI::welcome(void)
{
	std::string lines(MSG.length(), '-');
	std::cout << "\t\t" << MSG << std::endl;
	std::cout << "\t\t" << lines << std::endl;
}
