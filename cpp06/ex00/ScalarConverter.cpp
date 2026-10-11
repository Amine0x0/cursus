#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::~ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter&) {}
ScalarConverter& ScalarConverter::operator=(const ScalarConverter&) { return *this; }

bool ScalarConverter::isChar(const std::string& in) {
    if (in.length() == 1) {
        if (!std::isdigit(static_cast<unsigned char>(in[0])))
            return true;
    }
    return false;
}

bool ScalarConverter::isInt(const std::string& in) {
    char* end;
    std::strtol(in.c_str(), &end, 10);
    
    if (!in.empty() && end == in.c_str() + in.length()) {
        return true;
    }
    return false;
}

bool ScalarConverter::isFloat(const std::string& in) {
    if (in == "-inff" || in == "+inff" || in == "nanf") {
        return true;
    }

    if (in.empty() || in[in.length() - 1] != 'f') {
        return false;
    }

    char* end;
    std::strtod(in.c_str(), &end);

    if (end == in.c_str() + in.length() - 1) {
        return true;
    }

    return false;
}

bool ScalarConverter::isDouble(const std::string& in) {
    if (in == "-inf" || in == "+inf" || in == "nan") {
        return true;
    }

    char* end;
    std::strtod(in.c_str(), &end);

    if (!in.empty() && end == in.c_str() + in.length()) {
        return true;
    }

    return false;
}

void ScalarConverter::convert(const std::string& in) {
    if (in.empty()) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(1);

    if (ScalarConverter::isChar(in)) {
        char c = in[0];
        std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << std::endl;
    }
    
    else if (ScalarConverter::isInt(in)) {
        long lVal = std::strtol(in.c_str(), NULL, 10);

        std::cout << "char: ";
        if (lVal < 0 || lVal > 127) 
            std::cout << "impossible" << std::endl;
        else if (!std::isprint(static_cast<unsigned char>(lVal)))
            std::cout << "Non displayable" << std::endl;
        else
            std::cout << "'" << static_cast<char>(lVal) << "'" << std::endl;

        std::cout << "int: ";
        if (lVal < std::numeric_limits<int>::min() || lVal > std::numeric_limits<int>::max())
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(lVal) << std::endl;

        std::cout << "float: " << static_cast<float>(lVal) << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(lVal) << std::endl;
    }

    else if (ScalarConverter::isFloat(in)) {
        float fVal = static_cast<float>(std::strtod(in.c_str(), NULL));
        bool isPseudo = (in == "-inff" || in == "+inff" || in == "nanf");

        std::cout << "char: ";
        if (fVal < 0 || fVal > 127 || std::isnan(fVal)) 
            std::cout << "impossible" << std::endl;
        else if (!std::isprint(static_cast<unsigned char>(static_cast<int>(fVal))))
            std::cout << "Non displayable" << std::endl;
        else
            std::cout << "'" << static_cast<char>(fVal) << "'" << std::endl;

        std::cout << "int: ";
        if (isPseudo || fVal < static_cast<float>(std::numeric_limits<int>::min()) ||
            fVal > static_cast<float>(std::numeric_limits<int>::max()))
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(fVal) << std::endl;

        std::cout << "float: " << fVal << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(fVal) << std::endl;
    }

    else if (ScalarConverter::isDouble(in)) {
        double dVal = std::strtod(in.c_str(), NULL);
        bool isPseudo = (in == "-inf" || in == "+inf" || in == "nan");

        std::cout << "char: ";
        if (dVal < 0 || dVal > 127 || std::isnan(dVal)) 
            std::cout << "impossible" << std::endl;
        else if (!std::isprint(static_cast<unsigned char>(static_cast<int>(dVal))))
            std::cout << "Non displayable" << std::endl;
        else
            std::cout << "'" << static_cast<char>(dVal) << "'" << std::endl;

        std::cout << "int: ";
        if (isPseudo || dVal < static_cast<double>(std::numeric_limits<int>::min()) ||
            dVal > static_cast<double>(std::numeric_limits<int>::max()))
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<int>(dVal) << std::endl;

        std::cout << "float: ";
        if (!std::isnan(dVal) && (dVal > std::numeric_limits<float>::max() || dVal < -std::numeric_limits<float>::max()))
            std::cout << "impossible" << std::endl;
        else
            std::cout << static_cast<float>(dVal) << "f" << std::endl;

        std::cout << "double: " << dVal << std::endl;
    }

    else {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
    }
}