#include "../includes/Server.hpp"
#include "../includes/Arguments.hpp"
#include "../includes/Signals.hpp"

int main(int argc, char** argv){
    int port = 0;
    std::string password;

    if (!arguments::parse(argc, argv, port, password)) {
        return 1;
    }

    signals::install();

    Server server(port, password);
    if (!server.isReady()) {
        return 1;
    }

    server.run();
    return 0;
}
