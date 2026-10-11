#include <iostream>
#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	try
	{
		PmergeMe	pm;

		pm.parseArgs(argc, argv);
		pm.run();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}