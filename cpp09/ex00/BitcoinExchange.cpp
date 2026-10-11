#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange() : _rates(){}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &src) : _rates(src._rates){}

BitcoinExchange	&BitcoinExchange::operator=(BitcoinExchange const &other)
{
	if (this != &other)
		_rates = other._rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(){}

char const	*BitcoinExchange::FileException::what() const throw()
{
	return ("Error: could not open file.");
}


void	BitcoinExchange::loadDatabase(std::string const &path)
{
	std::ifstream	file(path.c_str());
	if (!file.is_open())
		throw FileException();

	std::string	line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		size_t	comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string	date = line.substr(0, comma);
		double		rate = std::strtod(line.substr(comma + 1).c_str(), NULL);
		_rates[date] = rate;
	}
}


void	BitcoinExchange::processInput(std::string const &path)
{
	std::ifstream	file(path.c_str());
	if (!file.is_open())
		throw FileException();

	std::string	line;
	if (!std::getline(file, line))
    	return ; 
	if (line != "date | value")
		handleLine(line);
	while (std::getline(file, line))
		handleLine(line);
}

bool	BitcoinExchange::isValidDate(std::string const &date) const
{
	if (date.length() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (size_t i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return (false);
	}

	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return (false);
	if (day < 1 || day > 31)
		return (false);
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return (false);
	if (month == 2)
	{
		bool	leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (leap ? 29 : 28))
			return (false);
	}
	return (true);
}

bool BitcoinExchange::getRate(std::string const &date, double &rate) const
{
    if (_rates.empty())
        return (false);

    std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);

    if (it != _rates.end() && it->first == date)
    {
        rate = it->second;
        return (true);
    }

    if (it == _rates.begin())
        return (false);

    --it;
    rate = it->second;
    return (true);
}

void BitcoinExchange::handleLine(std::string const &line) const
{
    if (line.empty())
    {
        std::cout << "Error: empty line" << std::endl;
        return ;
    }

    size_t sep = line.find(" | ");
    if (sep == std::string::npos)
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return ;
    }

    std::string date = line.substr(0, sep);
    std::string value = line.substr(sep + 3);

    if (!isValidDate(date))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return ;
    }

    char *end;
    double number = std::strtod(value.c_str(), &end);
    if (value.empty() || *end != '\0')
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return ;
    }

    if (number < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return ;
    }

    if (number > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return ;
    }

    double rate;
    if (!getRate(date, rate))
    {
        std::cout << "Error: date too far back => " << date << std::endl;
        return ;
    }

    std::cout << date << " => " << number << " = " << number * rate << std::endl;
}