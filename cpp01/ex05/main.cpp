#include "Harl.hpp"

int main() {
	Harl	harl;

	std::cout << "--- Testing DEBUG level ---" << std::endl;
	harl.complain("DEBUG");

	std::cout << "\n--- Testing INFO level ---" << std::endl;
	harl.complain("INFO");

	std::cout << "\n--- Testing WARNING level ---" << std::endl;
	harl.complain("WARNING");

	std::cout << "\n--- Testing ERROR level ---" << std::endl;
	harl.complain("ERROR");

	std::cout << "\n--- Testing invalid level ---" << std::endl;
	harl.complain("INVALID");

	std::cout << "\n--- Testing lowercase (should be invalid) ---" << std::endl;
	harl.complain("debug");

	return (0);
}
