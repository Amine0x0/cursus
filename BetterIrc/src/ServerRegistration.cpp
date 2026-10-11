#include "../includes/Server.hpp"
#include "../includes/Replies.hpp"
#include <cctype>

namespace {

    bool isSpecial(char c) {
        return std::string("[]\\`_^{|}").find(c) != std::string::npos;
    }

    bool isValidNickname(const std::string& nick) {
        if (nick.empty() || nick.length() > __MaxNickLength) {
            return false;
        }
        if (!std::isalpha(static_cast<unsigned char>(nick[0])) && !isSpecial(nick[0])) {
            return false;
        }
        for (size_t i = 1; i < nick.length(); ++i) {
            if (!std::isalnum(static_cast<unsigned char>(nick[i])) &&
                !isSpecial(nick[i]) && nick[i] != '-') {
                return false;
            }
        }
        return true;
    }

}

void Server::cmdPass(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (session.isRegistered()) {
        queueMessage(client_fd, replies::alreadyRegistered(getServerName(), session.getNick()));
        return;
    }
    if (decoder.getParams().empty()) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "PASS"));
        return;
    }
    if (decoder.getParams()[0] != this->_password) {
        queueMessage(client_fd, replies::passwdMismatch(getServerName(), session.getNick()));
        queueMessage(client_fd, replies::error("Password incorrect"));
        session.markForDisconnect();
        return;
    }

    session.setPassDone();
    tooling::PrettyLog(LOG_INFO, "[IRC] PASS accepted.");
    completeRegistration(client_fd);
}

void Server::cmdNick(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().empty()) {
        queueMessage(client_fd, replies::noNicknameGiven(getServerName(), session.getNick()));
        return;
    }

    const std::string new_nick = decoder.getParams()[0];
    if (!isValidNickname(new_nick)) {
        queueMessage(client_fd, replies::erroneusNickname(getServerName(), session.getNick(), new_nick));
        return;
    }

    const int owner_fd = findFdByNick(new_nick);
    if (owner_fd >= 0 && owner_fd != client_fd) {
        queueMessage(client_fd, replies::nicknameInUse(getServerName(), session.getNick(), new_nick));
        return;
    }

    if (session.isRegistered() && session.getNick() != new_nick) {
        queueToPeers(client_fd, replies::nickChange(session.getMask(), new_nick), true);
    }

    session.setNick(new_nick);
    session.setNickDone();
    tooling::PrettyLog(LOG_INFO, "[IRC] NICK set to: " + new_nick);
    completeRegistration(client_fd);
}

void Server::cmdUser(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (session.isRegistered()) {
        queueMessage(client_fd, replies::alreadyRegistered(getServerName(), session.getNick()));
        return;
    }
    if (decoder.getParams().size() < 4) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "USER"));
        return;
    }

    session.setUser(decoder.getParams()[0], decoder.getParams()[3]);
    session.setUserDone();
    tooling::PrettyLog(LOG_INFO, "[IRC] USER command received.");
    completeRegistration(client_fd);
}

void Server::completeRegistration(int client_fd) {
    Session& session = getSession(client_fd);

    if (!session.isNickDone() || !session.isUserDone()) {
        return;
    }
    if (!session.isPassDone()) {
        return;
    }
    if (session.isWelcomeSent()) {
        return;
    }

    const std::string& nick = session.getNick();
    queueMessage(client_fd, replies::welcome(getServerName(), nick));
    queueMessage(client_fd, replies::yourHost(getServerName(), nick));
    queueMessage(client_fd, replies::created(getServerName(), nick, _metadata.start_time));
    queueMessage(client_fd, replies::myInfo(getServerName(), nick));
    queueMessage(client_fd, replies::noMotd(getServerName(), nick));

    session.markWelcomeSent();
    tooling::PrettyLog(LOG_SUCCESS, "[IRC] Sent welcome burst to " + nick);
}

void Server::cmdQuit(int client_fd, const PacketDecoder& decoder) {
    const std::string reason = decoder.getParams().empty() ? "Client Quit" : decoder.getParams()[0];

    queueMessage(client_fd, replies::error("Closing link: " + reason));
    getSession(client_fd).markForDisconnect();
}

void Server::cmdPing(int client_fd, const PacketDecoder& decoder) {
    const std::string token = decoder.getParams().empty() ? getServerName() : decoder.getParams()[0];

    queueMessage(client_fd, replies::pong(getServerName(), token));
}


void Server::cmdPong(int, const PacketDecoder&) {}


void Server::cmdCap(int client_fd, const PacketDecoder& decoder) {
    if (decoder.getParams().empty()) {
        return;
    }

    Session& session = getSession(client_fd);
    const std::string& subcommand = decoder.getParams()[0];
    const std::string upper_subcommand = tooling::toUpper(subcommand);

    if (upper_subcommand == "LS") {
        queueMessage(client_fd, replies::capabilityList(getServerName(), session.getNick()));
    } else if (upper_subcommand == "REQ" && decoder.getParams().size() > 1) {
        queueMessage(client_fd, replies::capabilityNak(getServerName(), session.getNick(),
                                                       decoder.getParams()[1]));
    }
}


void Server::removeSessionFromChannels(int client_fd, const std::string& quit_reason) {
    Session& session = getSession(client_fd);

    if (session.isRegistered()) {
        queueToPeers(client_fd, replies::quit(session.getMask(), quit_reason), false);
    }

    std::map<std::string, Channel>::iterator it = _channels.begin();
    while (it != _channels.end()) {
        #if DEV_MODE
            if (it->second.isMember(client_fd)) {
                tooling::PrettyLog(LOG_DEV, "[IRC] " + session.getNick() +
                    " left channel " + it->second.getName() + " (QUIT)");
            }
        #endif
        it->second.removeMember(client_fd);

        if (it->second.isEmpty()) {
            std::map<std::string, Channel>::iterator empty_channel = it++;
            _channels.erase(empty_channel);
        } else if (!it->second.hasOperators()) {
            Channel& channel = it->second;
            const int new_op_fd = *channel.getMembers().begin();
            channel.promoteOperator(new_op_fd);

            const std::string new_op_nick = getSession(new_op_fd).getNick();
            const std::string mode_msg = ":" + getServerName() + " MODE " +
                channel.getName() + " +o " + new_op_nick + "\r\n";
            queueToChannel(channel, mode_msg, -1);
            ++it;
        } else {
            ++it;
        }
    }
}
