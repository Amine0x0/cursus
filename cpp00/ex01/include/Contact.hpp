#include "./Header.hpp"

class Contact
{
	private:
		std::string _firstname;
		std::string _lastname;
		std::string _nickname;
		std::string _phonenumber;
		std::string _secret;

	public:
		Contact();
		~Contact();

		void		setFirstName(std::string);
		void		setLastName(std::string);
		void		setNickname(std::string);
		void		setPhoneNumber(std::string);
		void		setSecret(std::string);

		std::string	getFirstName(void) const;
		std::string	getLastName(void) const;
		std::string	getNickname(void) const;
		std::string	getPhoneNumber(void) const;
		std::string	getSecret(void) const;

		void		display(void) const;
};