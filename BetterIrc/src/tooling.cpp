#include <iostream>
#include "../includes/Tooling.hpp"
#include <ctime>
#include <fstream>
#include <sstream>
#include <cctype>

const char* const Color::reset  = "\033[0m";
const char* const Color::red    = "\033[31m";
const char* const Color::green  = "\033[32m";
const char* const Color::yellow = "\033[33m";
const char* const Color::purple = "\033[35m";
const char* const Color::cyan   = "\033[36m";

std::string getCurrentTimestamp() {
    std::time_t now = std::time(NULL);
    std::tm* tm_info = std::localtime(&now);
    
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm_info);
    return std::string(buffer);
}

void PrintAsciiBanner() {
    std::string banner =                                                                        
    "\n\n\t@@@ @@@@@@@   @@@@@@@           @@@@@@ @@@@@@@@ @@@@@@@  @@@  @@@ @@@@@@@@ @@@@@@@\n"  
    "\t@@! @@!  @@@ !@@               !@@     @@!      @@!  @@@ @@!  @@@ @@!      @@!  @@@\n" 
    "\t!!@ @!@!!@!  !@!                !@@!!  @!!!:!   @!@!!@!  @!@  !@! @!!!:!   @!@!!@!\n"  
    "\t!!: !!: :!!  :!!                   !:! !!:      !!: :!!   !: .:!  !!:      !!: :!!\n"  
    "\t:    :   : :  :: :: : .......  ::.: :  : :: ::   :   : :    ::    : :: ::   :   : :\n" 
    "\t                    : :: : :\n"
    "\t\t\t\t\t\t\t\t\t-by @amabbadi\n";
    std::cout << Color::purple << banner << Color::reset << std::endl;
}

void tooling::PrettyLog(const LogType type, const std::string& msg){
    std::string timestamp = getCurrentTimestamp();
    std::string prefix = "[" + timestamp + "]: ";

    switch(type){
        case LOG_ERROR:
            std::cout << Color::red << prefix << msg << Color::reset << std::endl;
            break;
        case LOG_INFO:
            std::cout << Color::yellow << prefix << msg << Color::reset << std::endl;
            break;
        case LOG_SUCCESS:
            std::cout << Color::green << prefix << msg << Color::reset << std::endl;
            break;
        case LOG_DEV:
            std::cout << Color::cyan << prefix << msg << Color::reset << std::endl;
            break;
        default:
            std::cout << prefix << msg << std::endl;
            break;
    }
}

std::string tooling::toLower(const std::string& text) {
    std::string lowered(text);

    for (size_t i = 0; i < lowered.length(); ++i) {
        lowered[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(lowered[i])));
    }
    return lowered;
}

std::string tooling::toUpper(const std::string& text) {
    std::string uppered(text);

    for (size_t i = 0; i < uppered.length(); ++i) {
        uppered[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(uppered[i])));
    }
    return uppered;
}

std::string tooling::toString(size_t value) {
    std::stringstream stream;

    stream << value;
    return stream.str();
}

std::vector<std::string> tooling::split(const std::string& text, char separator) {
    std::vector<std::string> pieces;
    std::stringstream stream(text);
    std::string piece;

    while (std::getline(stream, piece, separator)) {
        pieces.push_back(piece);
    }
    return pieces;
}
