#include "Header.hpp"

class PhoneBook
{
	private:
		Contact		_contacts[8];
		int			_count;
		int			_index;
		ConsoleUI	_ui;
		std::string	_input;

		void		add(void);
		void		search(void);
		void		leave(void);
		void		invalid(void);
		void		process(void);

	public:
		PhoneBook();
		~PhoneBook();

		void		run(void);
};