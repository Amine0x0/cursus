#include "../includes/Server.hpp"
#include "../includes/Replies.hpp"
#include <cstdlib>

void Server::cmdMode(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().empty()) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "MODE"));
        return;
    }

    const std::string& target = decoder.getParams()[0];

    if (target.empty() || (target[0] != '#' && target[0] != '&')) {
        const int target_fd = findFdByNick(target);

        if (target_fd < 0) {
            queueMessage(client_fd, replies::noSuchNick(getServerName(), session.getNick(), target));
        } else if (target_fd != client_fd) {
            queueMessage(client_fd, replies::usersDontMatch(getServerName(), session.getNick()));
        } else {
            queueMessage(client_fd, replies::userModeIs(getServerName(), session.getNick()));
        }
        return;
    }

    Channel* channel = findChannel(target);
    if (channel == NULL) {
        queueMessage(client_fd, replies::noSuchChannel(getServerName(), session.getNick(), target));
        return;
    }

    if (decoder.getParams().size() < 2) {
        queueMessage(client_fd, replies::channelModeIs(getServerName(), session.getNick(),
                                                       channel->getName(),
                                                       channel->getModeFlags() + channel->getModeArguments()));
        return;
    }

    if (!channel->isMember(client_fd)) {
        queueMessage(client_fd, replies::notOnChannel(getServerName(), session.getNick(), channel->getName()));
        return;
    }
    if (!channel->isOperator(client_fd)) {
        queueMessage(client_fd, replies::chanOpPrivsNeeded(getServerName(), session.getNick(), channel->getName()));
        return;
    }

    applyChannelModes(client_fd, *channel, decoder);
}

void Server::applyChannelModes(int client_fd, Channel& channel, const PacketDecoder& decoder) {
    const std::vector<std::string>& params = decoder.getParams();
    const std::string& modes = params[1];

    size_t next_argument = 2;
    bool adding = true;
    char announced_sign = 0;
    std::string applied_flags;
    std::string applied_arguments;

    for (size_t i = 0; i < modes.length(); ++i) {
        const char mode = modes[i];

        if (mode == '+' || mode == '-') {
            adding = (mode == '+');
            continue;
        }

        const bool needs_argument = (mode == 'o') || (adding && (mode == 'k' || mode == 'l'));
        const bool takes_optional_argument = (!adding && mode == 'k');
        std::string argument;

        if (needs_argument || takes_optional_argument) {
            if (next_argument < params.size()) {
                argument = params[next_argument++];
            } else if (needs_argument) {
                queueMessage(client_fd, replies::needMoreParams(getServerName(),
                                                                getSession(client_fd).getNick(), "MODE"));
                continue;
            }
        }

        bool changed = false;
        switch (mode) {
            case 'i': changed = applyInviteOnly(channel, adding); break;
            case 't': changed = applyTopicLock(channel, adding); break;
            case 'k': changed = applyChannelKey(client_fd, channel, adding, argument); break;
            case 'o': changed = applyOperator(client_fd, channel, adding, argument); break;
            case 'l': changed = applyUserLimit(channel, adding, argument); break;
            default:
                queueMessage(client_fd, replies::unknownMode(getServerName(),
                                                             getSession(client_fd).getNick(), mode));
                continue;
        }

        if (changed) {
            if (announced_sign != (adding ? '+' : '-')) {
                announced_sign = adding ? '+' : '-';
                applied_flags += announced_sign;
            }
            applied_flags += mode;

            if (!argument.empty()) {
                applied_arguments += " " + argument;
            }
        }
    }

    if (!applied_flags.empty()) {
        queueToChannel(channel, replies::modeChanged(getSession(client_fd).getMask(), channel.getName(),
                                                     applied_flags + applied_arguments), -1);
    }
}

bool Server::applyInviteOnly(Channel& channel, bool adding) {
    if (channel.isInviteOnly() == adding) {
        return false;
    }
    channel.setInviteOnly(adding);
    return true;
}

bool Server::applyTopicLock(Channel& channel, bool adding) {
    if (channel.isTopicLocked() == adding) {
        return false;
    }
    channel.setTopicLocked(adding);
    return true;
}

bool Server::applyChannelKey(int client_fd, Channel& channel, bool adding, const std::string& argument) {
    if (adding) {
        if (argument.empty()) {
            queueMessage(client_fd, replies::needMoreParams(getServerName(),
                                                            getSession(client_fd).getNick(), "MODE"));
            return false;
        }
        channel.setKey(argument);
        return true;
    }

    if (!channel.hasKey()) {
        return false;
    }
    channel.clearKey();
    return true;
}

bool Server::applyOperator(int client_fd, Channel& channel, bool adding, const std::string& argument) {
    const int target_fd = findFdByNick(argument);

    if (target_fd < 0 || !channel.isMember(target_fd)) {
        queueMessage(client_fd, replies::userNotInChannel(getServerName(), getSession(client_fd).getNick(),
                                                          argument, channel.getName()));
        return false;
    }
    if (channel.isOperator(target_fd) == adding) {
        return false;
    }

    if (adding) {
        channel.promoteOperator(target_fd);
    } else {
        channel.demoteOperator(target_fd);
    }
    return true;
}

bool Server::applyUserLimit(Channel& channel, bool adding, const std::string& argument) {
    if (adding) {
        const long limit = std::atol(argument.c_str());

        if (limit <= 0) {
            return false;
        }
        channel.setUserLimit(static_cast<size_t>(limit));
        return true;
    }

    if (!channel.hasUserLimit()) {
        return false;
    }
    channel.clearUserLimit();
    return true;
}
