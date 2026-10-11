#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cmath>
#include <cstdlib>

class ScalarConverter {
    public:
        static void convert(const std::string& input);

    private:
        ScalarConverter();
        ~ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter& operator=(const ScalarConverter& other);

        static bool isChar(const std::string& in);
        static bool isInt(const std::string& in);
        static bool isFloat(const std::string& in);
        static bool isDouble(const std::string& in);
};

#endif