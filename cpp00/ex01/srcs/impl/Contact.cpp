#include "../../include/Header.hpp"

Contact::Contact() : _firstname(""), _lastname(""), _nickname(""), _phonenumber(""), _secret("") {}

Contact::~Contact() {}

void	Contact::setFirstName(std::string firstname)
{
	_firstname = firstname;
}

void	Contact::setLastName(std::string lastname)
{
	_lastname = lastname;
}

void	Contact::setNickname(std::string nickname)
{
	_nickname = nickname;
}

void	Contact::setPhoneNumber(std::string phonenumber)
{
	_phonenumber = phonenumber;
}

void	Contact::setSecret(std::string secret)
{
	_secret = secret;
}

std::string	Contact::getFirstName(void) const
{
	return (_firstname);
}

std::string	Contact::getLastName(void) const
{
	return (_lastname);
}

std::string	Contact::getNickname(void) const
{
	return (_nickname);
}

std::string	Contact::getPhoneNumber(void) const
{
	return (_phonenumber);
}

std::string	Contact::getSecret(void) const
{
	return (_secret);
}

void	Contact::display(void) const
{
	std::cout << "First Name: " << _firstname << std::endl;
	std::cout << "Last Name: " << _lastname << std::endl;
	std::cout << "Nickname: " << _nickname << std::endl;
	std::cout << "Phone Number: " << _phonenumber << std::endl;
	std::cout << "Darkest Secret: " << _secret << std::endl;
}