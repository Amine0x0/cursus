#include "../includes/Signals.hpp"

#include <csignal>

namespace {

    volatile sig_atomic_t g_stop_requested = 0;

    void requestStop(int) {
        g_stop_requested = 1;
    }

}

void signals::install() {
    std::signal(SIGINT, requestStop);
    std::signal(SIGTERM, requestStop);
    std::signal(SIGPIPE, SIG_IGN);
}

bool signals::stopRequested() {
    return g_stop_requested != 0;
}
