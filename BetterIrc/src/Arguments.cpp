#include "../includes/Arguments.hpp"
#include "../includes/Tooling.hpp"

#include <cstdlib>

namespace {

    bool isNumeric(const std::string& text) {
        if (text.empty()) {
            return false;
        }
        for (size_t i = 0; i < text.length(); ++i) {
            if (text[i] < '0' || text[i] > '9') {
                return false;
            }
        }
        return true;
    }

}

bool arguments::parse(int argc, char** argv, int& port, std::string& password) {
    if (argc != 3) {
        tooling::PrettyLog(LOG_ERROR, "usage: ./ircserv <port> <password>");
        return false;
    }

    const std::string raw_port(argv[1]);
    if (!isNumeric(raw_port)) {
        tooling::PrettyLog(LOG_ERROR, "port must be a positive number: " + raw_port);
        return false;
    }

    const long parsed_port = std::atol(raw_port.c_str());
    if (parsed_port < 1 || parsed_port > 65535) {
        tooling::PrettyLog(LOG_ERROR, "port must be in the 1-65535 range: " + raw_port);
        return false;
    }

    password = argv[2];
    if (password.empty()) {
        tooling::PrettyLog(LOG_ERROR, "password must not be empty");
        return false;
    }

    port = static_cast<int>(parsed_port);
    return true;
}
