#include "../includes/Replies.hpp"
#include "../includes/MasterControlFlags.hpp"

namespace {

    std::string numeric(const std::string& server, const std::string& code,
                        const std::string& nick, const std::string& middle,
                        const std::string& text) {
        std::string line = ":" + server + " " + code + " " + (nick.empty() ? "*" : nick);

        if (!middle.empty()) {
            line += " " + middle;
        }
        return line + " :" + text + "\r\n";
    }

    std::string relayed(const std::string& mask, const std::string& command,
                        const std::string& middle, const std::string& text) {
        std::string line = ":" + mask + " " + command;

        if (!middle.empty()) {
            line += " " + middle;
        }
        if (!text.empty()) {
            line += " :" + text;
        }
        return line + "\r\n";
    }

}

std::string replies::welcome(const std::string& server, const std::string& nick) {
    return numeric(server, "001", nick, "",
                   "Welcome to the Internet Relay Network " + nick);
}

std::string replies::yourHost(const std::string& server, const std::string& nick) {
    return numeric(server, "002", nick, "",
                   "Your host is " + server + ", running version " + __ServerVersion);
}

std::string replies::created(const std::string& server, const std::string& nick,
                            std::time_t created_at) {
    const char* raw_time = std::ctime(&created_at);
    const std::string creation_time = raw_time == NULL ? "unknown time" : raw_time;
    std::string text = creation_time;

    if (!text.empty() && text[text.length() - 1] == '\n') {
        text.erase(text.length() - 1);
    }
    return numeric(server, "003", nick, "", "This server was created " + text);
}

std::string replies::myInfo(const std::string& server, const std::string& nick) {
    return ":" + server + " 004 " + nick + " " + server + " " + __ServerVersion +
           " " + __UserModes + " " + __ChannelModes + "\r\n";
}

std::string replies::noMotd(const std::string& server, const std::string& nick) {
    return numeric(server, "422", nick, "", "MOTD File is missing");
}

std::string replies::userModeIs(const std::string& server, const std::string& nick) {
    return numeric(server, "221", nick, "", "+");
}


std::string replies::channelModeIs(const std::string& server, const std::string& nick,
                                   const std::string& channel, const std::string& modes) {
    return ":" + server + " 324 " + nick + " " + channel + " " + modes + "\r\n";
}

std::string replies::inviting(const std::string& server, const std::string& nick,
                              const std::string& target, const std::string& channel) {
    return ":" + server + " 341 " + nick + " " + target + " " + channel + "\r\n";
}

std::string replies::noTopic(const std::string& server, const std::string& nick,
                             const std::string& channel) {
    return numeric(server, "331", nick, channel, "No topic is set");
}

std::string replies::topic(const std::string& server, const std::string& nick,
                           const std::string& channel, const std::string& text) {
    return numeric(server, "332", nick, channel, text);
}

std::string replies::nameReply(const std::string& server, const std::string& nick,
                               const std::string& channel, const std::string& names) {
    return numeric(server, "353", nick, "= " + channel, names);
}

std::string replies::endOfNames(const std::string& server, const std::string& nick,
                                const std::string& channel) {
    return numeric(server, "366", nick, channel, "End of /NAMES list");
}


std::string replies::noSuchNick(const std::string& server, const std::string& nick,
                                const std::string& target) {
    return numeric(server, "401", nick, target, "No such nick/channel");
}

std::string replies::noSuchChannel(const std::string& server, const std::string& nick,
                                   const std::string& channel) {
    return numeric(server, "403", nick, channel, "No such channel");
}

std::string replies::cannotSendToChan(const std::string& server, const std::string& nick,
                                      const std::string& channel) {
    return numeric(server, "404", nick, channel, "Cannot send to channel");
}

std::string replies::noRecipient(const std::string& server, const std::string& nick,
                                 const std::string& command) {
    return numeric(server, "411", nick, "", "No recipient given (" + command + ")");
}

std::string replies::noTextToSend(const std::string& server, const std::string& nick) {
    return numeric(server, "412", nick, "", "No text to send");
}

std::string replies::unknownCommand(const std::string& server, const std::string& nick,
                                    const std::string& command) {
    return numeric(server, "421", nick, command, "Unknown command");
}

std::string replies::noNicknameGiven(const std::string& server, const std::string& nick) {
    return numeric(server, "431", nick, "", "No nickname given");
}

std::string replies::erroneusNickname(const std::string& server, const std::string& nick,
                                      const std::string& wanted) {
    return numeric(server, "432", nick, wanted, "Erroneous nickname");
}

std::string replies::nicknameInUse(const std::string& server, const std::string& nick,
                                   const std::string& wanted) {
    return numeric(server, "433", nick, wanted, "Nickname is already in use");
}

std::string replies::userNotInChannel(const std::string& server, const std::string& nick,
                                      const std::string& target, const std::string& channel) {
    return numeric(server, "441", nick, target + " " + channel,
                   "They aren't on that channel");
}

std::string replies::notOnChannel(const std::string& server, const std::string& nick,
                                  const std::string& channel) {
    return numeric(server, "442", nick, channel, "You're not on that channel");
}

std::string replies::userOnChannel(const std::string& server, const std::string& nick,
                                   const std::string& target, const std::string& channel) {
    return numeric(server, "443", nick, target + " " + channel,
                   "is already on channel");
}

std::string replies::notRegistered(const std::string& server, const std::string& nick) {
    return numeric(server, "451", nick, "", "You have not registered");
}

std::string replies::needMoreParams(const std::string& server, const std::string& nick,
                                    const std::string& command) {
    return numeric(server, "461", nick, command, "Not enough parameters");
}

std::string replies::alreadyRegistered(const std::string& server, const std::string& nick) {
    return numeric(server, "462", nick, "", "You may not reregister");
}

std::string replies::passwdMismatch(const std::string& server, const std::string& nick) {
    return numeric(server, "464", nick, "", "Password incorrect");
}

std::string replies::channelIsFull(const std::string& server, const std::string& nick,
                                   const std::string& channel) {
    return numeric(server, "471", nick, channel, "Cannot join channel (+l)");
}

std::string replies::unknownMode(const std::string& server, const std::string& nick,
                                 char mode) {
    return numeric(server, "472", nick, std::string(1, mode),
                   "is unknown mode char to me");
}

std::string replies::inviteOnlyChan(const std::string& server, const std::string& nick,
                                    const std::string& channel) {
    return numeric(server, "473", nick, channel, "Cannot join channel (+i)");
}

std::string replies::badChannelKey(const std::string& server, const std::string& nick,
                                   const std::string& channel) {
    return numeric(server, "475", nick, channel, "Cannot join channel (+k)");
}

std::string replies::badChanMask(const std::string& server, const std::string& nick,
                                 const std::string& channel) {
    return numeric(server, "476", nick, channel, "Bad Channel Mask");
}

std::string replies::chanOpPrivsNeeded(const std::string& server, const std::string& nick,
                                       const std::string& channel) {
    return numeric(server, "482", nick, channel, "You're not channel operator");
}

std::string replies::usersDontMatch(const std::string& server, const std::string& nick) {
    return numeric(server, "502", nick, "", "Cannot change mode for other users");
}

std::string replies::whoReply(const std::string& server, const std::string& nick,
                              const std::string& channel, const std::string& user,
                              const std::string& host, const std::string& member_nick,
                              const std::string& flags, const std::string& realname) {
    return ":" + server + " 352 " + nick + " " + channel + " " + user + " " + host +
           " " + server + " " + member_nick + " " + flags + " :0 " + realname + "\r\n";
}

std::string replies::endOfWho(const std::string& server, const std::string& nick,
                              const std::string& target) {
    return numeric(server, "315", nick, target, "End of /WHO list.");
}


std::string replies::join(const std::string& mask, const std::string& channel) {
    return relayed(mask, "JOIN", channel, "");
}

std::string replies::part(const std::string& mask, const std::string& channel,
                          const std::string& reason) {
    return relayed(mask, "PART", channel, reason);
}

std::string replies::quit(const std::string& mask, const std::string& reason) {
    return relayed(mask, "QUIT", "", reason);
}

std::string replies::nickChange(const std::string& mask, const std::string& new_nick) {
    return relayed(mask, "NICK", "", new_nick);
}

std::string replies::privmsg(const std::string& mask, const std::string& target,
                             const std::string& text) {
    return relayed(mask, "PRIVMSG", target, text);
}

std::string replies::notice(const std::string& mask, const std::string& target,
                            const std::string& text) {
    return relayed(mask, "NOTICE", target, text);
}

std::string replies::kick(const std::string& mask, const std::string& channel,
                          const std::string& target, const std::string& comment) {
    return relayed(mask, "KICK", channel + " " + target, comment);
}

std::string replies::invite(const std::string& mask, const std::string& target,
                            const std::string& channel) {
    return ":" + mask + " INVITE " + target + " " + channel + "\r\n";
}

std::string replies::topicChanged(const std::string& mask, const std::string& channel,
                                  const std::string& text) {
    return ":" + mask + " TOPIC " + channel + " :" + text + "\r\n";
}

std::string replies::modeChanged(const std::string& mask, const std::string& channel,
                                 const std::string& changes) {
    return ":" + mask + " MODE " + channel + " " + changes + "\r\n";
}


std::string replies::pong(const std::string& server, const std::string& token) {
    return ":" + server + " PONG " + server + " :" + token + "\r\n";
}

std::string replies::capabilityList(const std::string& server, const std::string& nick) {
    const std::string target = nick.empty() ? "*" : nick;
    return ":" + server + " CAP " + target + " LS :\r\n";
}

std::string replies::capabilityAck(const std::string& server, const std::string& nick,
                                   const std::string& capabilities) {
    const std::string target = nick.empty() ? "*" : nick;
    return ":" + server + " CAP " + target + " ACK :" + capabilities + "\r\n";
}

std::string replies::capabilityNak(const std::string& server, const std::string& nick,
                                   const std::string& capabilities) {
    const std::string target = nick.empty() ? "*" : nick;
    return ":" + server + " CAP " + target + " NAK :" + capabilities + "\r\n";
}

std::string replies::error(const std::string& reason) {
    return "ERROR :" + reason + "\r\n";
}
