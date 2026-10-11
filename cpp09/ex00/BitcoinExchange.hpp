#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
# include <map>
# include <string>
# include <exception>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_rates;

	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &src);
		BitcoinExchange	&operator=(BitcoinExchange const &rhs);
		~BitcoinExchange();

		void	loadDatabase(std::string const &path);

		void	processInput(std::string const &path);

		class FileException : public std::exception
		{
			public:
				virtual char const	*what() const throw();
		};

	private:
		bool	isValidDate(std::string const &date) const;
		bool	getRate(std::string const &date, double &rate) const;
		void	handleLine(std::string const &line) const;
};

#endif