#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];
            for (size_t j = 0; j < arg.size(); j++)
                arg[j] = std::toupper(arg[j]);
            std::cout << arg;
            if (i < argc - 1)
                std::cout << " ";
        }
        std::cout << std::endl;
    }
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
}
