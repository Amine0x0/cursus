#include "../includes/Server.hpp"
#include "../includes/Replies.hpp"
#include <sys/socket.h>
#include <unistd.h>

const std::string& Server::getServerName() const {
    return this->_metadata._servername;
}

Session& Server::getSession(int client_fd) {
    return this->_sessions[client_fd];
}

int Server::findFdByNick(const std::string& nick) {
    const std::string wanted = tooling::toLower(nick);

    for (std::map<int, Session>::iterator it = _sessions.begin(); it != _sessions.end(); ++it) {
        if (tooling::toLower(it->second.getNick()) == wanted) {
            return it->first;
        }
    }
    return -1;
}

Channel* Server::findChannel(const std::string& name) {
    std::map<std::string, Channel>::iterator it = _channels.find(tooling::toLower(name));

    if (it == _channels.end()) {
        return NULL;
    }
    return &it->second;
}

struct pollfd* Server::findPollEntry(int client_fd) {
    for (size_t i = 0; i < this->_fds.size(); ++i) {
        if (this->_fds[i].fd == client_fd) {
            return &this->_fds[i];
        }
    }
    return NULL;
}

void Server::queueMessage(int client_fd, const std::string& message) {
    std::map<int, Session>::iterator session = _sessions.find(client_fd);

    if (session == _sessions.end()) {
        return;
    }
    if (message.length() > __MaxPendingOutput ||
        session->second.getOutput().length() > __MaxPendingOutput - message.length()) {
        session->second.getOutput().clear();
        session->second.markForDisconnect();
        return;
    }
    session->second.queueOutput(message);

    struct pollfd* entry = findPollEntry(client_fd);
    if (entry != NULL) {
        entry->events = POLLIN | POLLOUT;
    }
}

void Server::queueToChannel(const Channel& channel, const std::string& message, int except_fd) {
    const std::set<int>& members = channel.getMembers();

    for (std::set<int>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (*it != except_fd) {
            queueMessage(*it, message);
        }
    }
}

void Server::queueToPeers(int client_fd, const std::string& message, bool include_self) {
    std::set<int> peers;

    for (std::map<std::string, Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
        if (it->second.isMember(client_fd)) {
            const std::set<int>& members = it->second.getMembers();
            peers.insert(members.begin(), members.end());
        }
    }

    if (include_self) {
        peers.insert(client_fd);
    } else {
        peers.erase(client_fd);
    }

    for (std::set<int>::const_iterator it = peers.begin(); it != peers.end(); ++it) {
        queueMessage(*it, message);
    }
}

void Server::flushClientOutput(int client_fd) {
    Session& session = getSession(client_fd);
    std::string& pending = session.getOutput();

    if (!pending.empty()) {
        int bytes_sent = send(client_fd, pending.c_str(), pending.length(), 0);

        if (bytes_sent > 0) {
            pending.erase(0, bytes_sent);
        } else if (bytes_sent == 0) {
            pending.clear();
            session.markForDisconnect();
            return;
        } else {
            return;
        }
    }

    if (pending.empty()) {
        struct pollfd* entry = findPollEntry(client_fd);
        if (entry != NULL) {
            entry->events = POLLIN;
        }
    }
}

void Server::reapClosedSessions() {
    std::vector<int> closing;

    for (std::map<int, Session>::iterator it = _sessions.begin(); it != _sessions.end(); ++it) {
        if (it->second.shouldDisconnect() && !it->second.hasPendingOutput()) {
            closing.push_back(it->first);
        }
    }

    for (size_t i = 0; i < closing.size(); ++i) {
        closeSession(closing[i]);
    }
}

void Server::closeSession(int client_fd) {
    removeSessionFromChannels(client_fd, "Connection closed");

    for (size_t i = 0; i < this->_fds.size(); ++i) {
        if (this->_fds[i].fd == client_fd) {
            this->_fds.erase(this->_fds.begin() + i);
            break;
        }
    }

    this->_sessions.erase(client_fd);
    close(client_fd);
    tooling::PrettyLog(LOG_INFO, "[IRC] Client disconnected.");
}
