#include "../includes/Server.hpp"
#include "../includes/Replies.hpp"

namespace {

    bool isValidChannelName(const std::string& name) {
        if (name.length() < 2 || (name[0] != '#' && name[0] != '&')) {
            return false;
        }
        return name.find(' ') == std::string::npos &&
               name.find(',') == std::string::npos &&
               name.find('\a') == std::string::npos;
    }

}

void Server::cmdJoin(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().empty()) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "JOIN"));
        return;
    }

    const std::vector<std::string> names = tooling::split(decoder.getParams()[0], ',');
    const std::vector<std::string> keys = decoder.getParams().size() > 1
        ? tooling::split(decoder.getParams()[1], ',')
        : std::vector<std::string>();

    for (size_t i = 0; i < names.size(); ++i) {
        joinChannel(client_fd, names[i], i < keys.size() ? keys[i] : "");
    }
}

void Server::cmdWho(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().empty()) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "WHO"));
        return;
    }

    const std::string& target = decoder.getParams()[0];
    Channel* channel = findChannel(target);
    if (channel != NULL) {
        const std::set<int>& members = channel->getMembers();
        for (std::set<int>::const_iterator it = members.begin(); it != members.end(); ++it) {
            const Session& member = getSession(*it);
            const std::string flags = channel->isOperator(*it) ? "H@" : "H";
            queueMessage(client_fd, replies::whoReply(getServerName(), session.getNick(),
                                                       channel->getName(), member.getUser(),
                                                       member.getHostname(), member.getNick(),
                                                       flags, member.getRealName()));
        }
    }

    queueMessage(client_fd, replies::endOfWho(getServerName(), session.getNick(), target));
}

void Server::joinChannel(int client_fd, const std::string& name, const std::string& key) {
    Session& session = getSession(client_fd);

    if (!isValidChannelName(name)) {
        queueMessage(client_fd, replies::badChanMask(getServerName(), session.getNick(), name));
        return;
    }

    Channel* channel = findChannel(name);

    if (channel == NULL) {
        _channels[tooling::toLower(name)] = Channel(name);
        channel = findChannel(name);
        channel->addMember(client_fd);
        channel->promoteOperator(client_fd);
        tooling::PrettyLog(LOG_SUCCESS, "[IRC] Channel created: " + name);
    } else {
        if (channel->isMember(client_fd)) {
            return;
        }
        if (channel->isInviteOnly() && !channel->isInvited(client_fd)) {
            queueMessage(client_fd, replies::inviteOnlyChan(getServerName(), session.getNick(), channel->getName()));
            return;
        }
        if (channel->hasKey() && channel->getKey() != key) {
            queueMessage(client_fd, replies::badChannelKey(getServerName(), session.getNick(), channel->getName()));
            return;
        }
        if (channel->isFull()) {
            queueMessage(client_fd, replies::channelIsFull(getServerName(), session.getNick(), channel->getName()));
            return;
        }
        channel->addMember(client_fd);
    }

    queueToChannel(*channel, replies::join(session.getMask(), channel->getName()), -1);
    sendChannelEntry(client_fd, *channel);
}

void Server::sendChannelEntry(int client_fd, const Channel& channel) {
    Session& session = getSession(client_fd);

    if (channel.hasTopic()) {
        queueMessage(client_fd, replies::topic(getServerName(), session.getNick(),
                                               channel.getName(), channel.getTopic()));
    } else {
        queueMessage(client_fd, replies::noTopic(getServerName(), session.getNick(), channel.getName()));
    }

    std::string names;
    const std::set<int>& members = channel.getMembers();
    for (std::set<int>::const_iterator it = members.begin(); it != members.end(); ++it) {
        if (!names.empty()) {
            names += " ";
        }
        if (channel.isOperator(*it)) {
            names += "@";
        }
        names += getSession(*it).getNick();
    }

    queueMessage(client_fd, replies::nameReply(getServerName(), session.getNick(), channel.getName(), names));
    queueMessage(client_fd, replies::endOfNames(getServerName(), session.getNick(), channel.getName()));
}

void Server::cmdPart(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().empty()) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "PART"));
        return;
    }

    const std::vector<std::string> names = tooling::split(decoder.getParams()[0], ',');
    const std::string reason = decoder.getParams().size() > 1 ? decoder.getParams()[1] : session.getNick();

    for (size_t i = 0; i < names.size(); ++i) {
        Channel* channel = findChannel(names[i]);

        if (channel == NULL) {
            queueMessage(client_fd, replies::noSuchChannel(getServerName(), session.getNick(), names[i]));
            continue;
        }
        if (!channel->isMember(client_fd)) {
            queueMessage(client_fd, replies::notOnChannel(getServerName(), session.getNick(), channel->getName()));
            continue;
        }

        queueToChannel(*channel, replies::part(session.getMask(), channel->getName(), reason), -1);

        channel->removeMember(client_fd);

        #if DEV_MODE
            tooling::PrettyLog(LOG_DEV, "[IRC] " + session.getNick() +
                " left channel " + channel->getName() + " (PART)");
        #endif

        if (channel->isEmpty()) {
            _channels.erase(tooling::toLower(channel->getName()));
        } else if (!channel->hasOperators()) {
            int new_op_fd = *channel->getMembers().begin();
            channel->promoteOperator(new_op_fd);

            std::string new_op_nick = getSession(new_op_fd).getNick();
            std::string mode_msg = ":" + getServerName() + " MODE " + channel->getName() + " +o " + new_op_nick + "\r\n";
            queueToChannel(*channel, mode_msg, -1);
        }
    }
}

void Server::cmdTopic(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().empty()) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "TOPIC"));
        return;
    }

    Channel* channel = findChannel(decoder.getParams()[0]);
    if (channel == NULL) {
        queueMessage(client_fd, replies::noSuchChannel(getServerName(), session.getNick(), decoder.getParams()[0]));
        return;
    }
    if (!channel->isMember(client_fd)) {
        queueMessage(client_fd, replies::notOnChannel(getServerName(), session.getNick(), channel->getName()));
        return;
    }

    if (decoder.getParams().size() < 2) {
        if (channel->hasTopic()) {
            queueMessage(client_fd, replies::topic(getServerName(), session.getNick(),
                                                   channel->getName(), channel->getTopic()));
        } else {
            queueMessage(client_fd, replies::noTopic(getServerName(), session.getNick(), channel->getName()));
        }
        return;
    }

    if (channel->isTopicLocked() && !channel->isOperator(client_fd)) {
        queueMessage(client_fd, replies::chanOpPrivsNeeded(getServerName(), session.getNick(), channel->getName()));
        return;
    }

    channel->setTopic(decoder.getParams()[1]);
    queueToChannel(*channel, replies::topicChanged(session.getMask(), channel->getName(),
                                                   channel->getTopic()), -1);
}

void Server::cmdInvite(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().size() < 2) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "INVITE"));
        return;
    }

    const std::string& target_nick = decoder.getParams()[0];
    Channel* channel = findChannel(decoder.getParams()[1]);

    if (channel == NULL) {
        queueMessage(client_fd, replies::noSuchChannel(getServerName(), session.getNick(), decoder.getParams()[1]));
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

    const int target_fd = findFdByNick(target_nick);
    if (target_fd < 0) {
        queueMessage(client_fd, replies::noSuchNick(getServerName(), session.getNick(), target_nick));
        return;
    }
    if (channel->isMember(target_fd)) {
        queueMessage(client_fd, replies::userOnChannel(getServerName(), session.getNick(),
                                                       target_nick, channel->getName()));
        return;
    }

    channel->inviteMember(target_fd);
    queueMessage(client_fd, replies::inviting(getServerName(), session.getNick(),
                                              getSession(target_fd).getNick(), channel->getName()));
    queueMessage(target_fd, replies::invite(session.getMask(), getSession(target_fd).getNick(),
                                            channel->getName()));
}

void Server::cmdKick(int client_fd, const PacketDecoder& decoder) {
    Session& session = getSession(client_fd);

    if (decoder.getParams().size() < 2) {
        queueMessage(client_fd, replies::needMoreParams(getServerName(), session.getNick(), "KICK"));
        return;
    }

    Channel* channel = findChannel(decoder.getParams()[0]);
    if (channel == NULL) {
        queueMessage(client_fd, replies::noSuchChannel(getServerName(), session.getNick(), decoder.getParams()[0]));
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

    const std::vector<std::string> targets = tooling::split(decoder.getParams()[1], ',');
    const std::string comment = decoder.getParams().size() > 2 ? decoder.getParams()[2] : session.getNick();

    for (size_t i = 0; i < targets.size(); ++i) {
        const int target_fd = findFdByNick(targets[i]);

        if (target_fd < 0) {
            queueMessage(client_fd, replies::noSuchNick(getServerName(), session.getNick(), targets[i]));
            continue;
        }
        if (!channel->isMember(target_fd)) {
            queueMessage(client_fd, replies::userNotInChannel(getServerName(), session.getNick(),
                targets[i], channel->getName()));
            continue;
        }

        queueToChannel(*channel, replies::kick(session.getMask(), channel->getName(),
                                               getSession(target_fd).getNick(), comment), -1);

        channel->removeMember(target_fd);

        if (!channel->isEmpty() && !channel->hasOperators()) {
            int new_op_fd = *channel->getMembers().begin();
            channel->promoteOperator(new_op_fd);

            std::string new_op_nick = getSession(new_op_fd).getNick();
            std::string mode_msg = ":" + getServerName() + " MODE " + channel->getName() + " +o " + new_op_nick + "\r\n";
            queueToChannel(*channel, mode_msg, -1);
        }
    }

    if (channel->isEmpty()) {
        _channels.erase(tooling::toLower(channel->getName()));
    }
}