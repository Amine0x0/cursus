#include "../includes/Server.hpp"
#include "../includes/Replies.hpp"

void Server::cmdPrivmsg(int client_fd, const PacketDecoder& decoder) {
    deliverMessage(client_fd, decoder, false);
}

void Server::cmdNotice(int client_fd, const PacketDecoder& decoder) {
    deliverMessage(client_fd, decoder, true);
}

void Server::deliverMessage(int client_fd, const PacketDecoder& decoder, bool is_notice) {
    Session& sender = getSession(client_fd);
    const std::vector<std::string>& params = decoder.getParams();
    const std::string command = is_notice ? "NOTICE" : "PRIVMSG";

    if (params.empty()) {
        if (!is_notice) {
            queueMessage(client_fd, replies::noRecipient(getServerName(), sender.getNick(), command));
        }
        return;
    }
    if (params.size() < 2 || params[1].empty()) {
        if (!is_notice) {
            queueMessage(client_fd, replies::noTextToSend(getServerName(), sender.getNick()));
        }
        return;
    }

    const std::string& text = params[1];
    const std::vector<std::string> targets = tooling::split(params[0], ',');

    for (size_t i = 0; i < targets.size(); ++i) {
        const std::string& target = targets[i];

        if (target.empty()) continue;

        if (target[0] == '#' || target[0] == '&') {
            Channel* channel = findChannel(target);

            if (channel == NULL || !channel->isMember(client_fd)) {
                if (!is_notice) {
                    queueMessage(client_fd, replies::cannotSendToChan(getServerName(), sender.getNick(), target));
                }
                continue;
            }
            const std::string message = is_notice
                ? replies::notice(sender.getMask(), target, text)
                : replies::privmsg(sender.getMask(), target, text);
            queueToChannel(*channel, message, client_fd);
        } else {
            const int target_fd = findFdByNick(target);

            if (target_fd < 0) {
                if (!is_notice) {
                    queueMessage(client_fd, replies::noSuchNick(getServerName(), sender.getNick(), target));
                }
                continue;
            }
            const std::string message = is_notice
                ? replies::notice(sender.getMask(), target, text)
                : replies::privmsg(sender.getMask(), target, text);
            queueMessage(target_fd, message);
        }
    }
}
