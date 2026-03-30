#include "../../include/Header.hpp"

PhoneBook::PhoneBook() : _count(0), _index(0) {}

PhoneBook::~PhoneBook() {}

void	PhoneBook::run(void)
{
	_ui.welcome();

	while (true)
	{
		std::cout << "> ";
		if (!(getline(std::cin, _input)))
			break;

		process();
		_input.clear();
	}
}

void	PhoneBook::process(void)
{
	if (!(_input.empty()))
	{
		if (_input == "ADD")
			add();
		else if (_input == "EXIT")
			leave();
		else if (_input == "SEARCH")
			search();
		else
			invalid();
	}
}

void	PhoneBook::invalid(void)
{
	_ui.print("command not found. [HELP : 'SEARCH', 'ADD', 'EXIT']");
}

void	PhoneBook::add(void)
{
	Contact new_contact;
	std::string temp;

	std::cout << "Enter first name: ";
	if (!getline(std::cin, temp))
		return ;
	while (temp.empty() || !is_printable(temp))
	{
		if (temp.empty())
			_ui.print("Error: first name cannot be empty");
		else
			_ui.print("Error: first name must contain only printable characters");
		std::cout << "Enter first name: ";
		if (!getline(std::cin, temp))
			return ;
	}
	new_contact.setFirstName(temp);

	std::cout << "Enter last name: ";
	if (!getline(std::cin, temp))
		return ;
	while (temp.empty() || !is_printable(temp))
	{
		if (temp.empty())
			_ui.print("Error: last name cannot be empty");
		else
			_ui.print("Error: last name must contain only printable characters");
		std::cout << "Enter last name: ";
		if (!getline(std::cin, temp))
			return ;
	}
	new_contact.setLastName(temp);

	std::cout << "Enter nickname: ";
	if (!getline(std::cin, temp))
		return ;
	while (temp.empty() || !is_printable(temp))
	{
		if (temp.empty())
			_ui.print("Error: nickname cannot be empty");
		else
			_ui.print("Error: nickname must contain only printable characters");
		std::cout << "Enter nickname: ";
		if (!getline(std::cin, temp))
			return ;
	}
	new_contact.setNickname(temp);

	std::cout << "Enter phone number: ";
	if (!getline(std::cin, temp))
		return ;
	while (temp.empty() || !is_valid_phone(temp))
	{
		if (temp.empty())
			_ui.print("Error: phone number cannot be empty");
		else
			_ui.print("Error: phone number must contain only digits");
		std::cout << "Enter phone number: ";
		if (!getline(std::cin, temp))
			return ;
	}
	new_contact.setPhoneNumber(temp);

	std::cout << "Enter darkest secret: ";
	if (!getline(std::cin, temp))
		return ;
	while (temp.empty() || !is_printable(temp))
	{
		if (temp.empty())
			_ui.print("Error: darkest secret cannot be empty");
		else
			_ui.print("Error: darkest secret must contain only printable characters");
		std::cout << "Enter darkest secret: ";
		if (!getline(std::cin, temp))
			return ;
	}
	new_contact.setSecret(temp);

	_contacts[_index] = new_contact;
	_index = (_index + 1) % 8;
	if (_count < 8)
		_count++;
	_ui.print("Contact added successfully");
}

void	PhoneBook::leave(void)
{
	_ui.print("leaving...");
	exit(0);
}

std::string	truncate(std::string str, int width)
{
	if ((int)str.length() > width)
	{
		str = str.substr(0, width - 1);
		str += '.';
	}
	return (str);
}

bool	is_valid_phone(std::string phone)
{
	if (phone.empty())
		return (false);

	for (size_t i = 0; i < phone.length(); i++)
	{
		if (!std::isdigit(phone[i]))
			return (false);
	}
	return (true);
}

bool	is_printable(std::string str)
{
	if (str.empty())
		return (false);

	for (size_t i = 0; i < str.length(); i++)
	{
		if (!std::isprint(str[i]))
			return (false);
	}
	return (true);
}

void	PhoneBook::search(void)
{
	if (_count == 0)
	{
		_ui.print("No contacts yet");
		return ;
	}

	std::cout << "|" << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << "|" << std::endl;

	for (int i = 0; i < _count; i++)
	{
		std::cout << "|" << std::setw(10) << i << "|"
				  << std::setw(10) << truncate(_contacts[i].getFirstName(), 10) << "|"
				  << std::setw(10) << truncate(_contacts[i].getLastName(), 10) << "|"
				  << std::setw(10) << truncate(_contacts[i].getNickname(), 10) << "|"
				  << std::endl;
	}

	std::cout << "Enter index to display: ";

	std::string input;
	if (!getline(std::cin, input) || input.empty())
	{
		_ui.print("Invalid index");
		return ;
	}

	int index = 0;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (!isdigit(input[i]))
		{
			_ui.print("Invalid index");
			return ;
		}
		index = index * 10 + (input[i] - '0');
	}

	if (index < 0 || index >= _count)
	{
		_ui.print("Invalid index");
		return ;
	}

	_contacts[index].display();
}
