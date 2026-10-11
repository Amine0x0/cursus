#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <string>

namespace arguments {
    bool parse(int argc, char** argv, int& port, std::string& password);
}

#endif
