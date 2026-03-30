#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cctype>

#include "ConsoleUI.hpp"
#include "Contact.hpp"
#include "PhoneBook.hpp"

std::string truncate(std::string str, int width);
bool is_valid_phone(std::string phone);
bool is_printable(std::string str);

#endif
