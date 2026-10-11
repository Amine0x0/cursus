#ifndef REPLIES_HPP
#define REPLIES_HPP

#include <ctime>
#include <string>

namespace replies {

    std::string welcome(const std::string& server, const std::string& nick);
    std::string yourHost(const std::string& server, const std::string& nick);
    std::string created(const std::string& server, const std::string& nick,
                        std::time_t created_at);
    std::string myInfo(const std::string& server, const std::string& nick);
    std::string noMotd(const std::string& server, const std::string& nick);
    std::string userModeIs(const std::string& server, const std::string& nick);

    std::string channelModeIs(const std::string& server, const std::string& nick,
                              const std::string& channel, const std::string& modes);
    std::string inviting(const std::string& server, const std::string& nick,
                         const std::string& target, const std::string& channel);
    std::string noTopic(const std::string& server, const std::string& nick,
                        const std::string& channel);
    std::string topic(const std::string& server, const std::string& nick,
                      const std::string& channel, const std::string& text);
    std::string nameReply(const std::string& server, const std::string& nick,
                          const std::string& channel, const std::string& names);
    std::string endOfNames(const std::string& server, const std::string& nick,
                           const std::string& channel);

    std::string noSuchNick(const std::string& server, const std::string& nick,
                           const std::string& target);
    std::string noSuchChannel(const std::string& server, const std::string& nick,
                              const std::string& channel);
    std::string cannotSendToChan(const std::string& server, const std::string& nick,
                                 const std::string& channel);
    std::string noRecipient(const std::string& server, const std::string& nick,
                            const std::string& command);
    std::string noTextToSend(const std::string& server, const std::string& nick);
    std::string unknownCommand(const std::string& server, const std::string& nick,
                               const std::string& command);
    std::string noNicknameGiven(const std::string& server, const std::string& nick);
    std::string erroneusNickname(const std::string& server, const std::string& nick,
                                 const std::string& wanted);
    std::string nicknameInUse(const std::string& server, const std::string& nick,
                              const std::string& wanted);
    std::string userNotInChannel(const std::string& server, const std::string& nick,
                                 const std::string& target, const std::string& channel);
    std::string notOnChannel(const std::string& server, const std::string& nick,
                             const std::string& channel);
    std::string userOnChannel(const std::string& server, const std::string& nick,
                              const std::string& target, const std::string& channel);
    std::string notRegistered(const std::string& server, const std::string& nick);
    std::string needMoreParams(const std::string& server, const std::string& nick,
                               const std::string& command);
    std::string alreadyRegistered(const std::string& server, const std::string& nick);
    std::string passwdMismatch(const std::string& server, const std::string& nick);
    std::string channelIsFull(const std::string& server, const std::string& nick,
                              const std::string& channel);
    std::string unknownMode(const std::string& server, const std::string& nick,
                            char mode);
    std::string inviteOnlyChan(const std::string& server, const std::string& nick,
                               const std::string& channel);
    std::string badChannelKey(const std::string& server, const std::string& nick,
                              const std::string& channel);
    std::string badChanMask(const std::string& server, const std::string& nick,
                            const std::string& channel);
    std::string chanOpPrivsNeeded(const std::string& server, const std::string& nick,
                                  const std::string& channel);
    std::string usersDontMatch(const std::string& server, const std::string& nick);
    std::string whoReply(const std::string& server, const std::string& nick,
                         const std::string& channel, const std::string& user,
                         const std::string& host, const std::string& member_nick,
                         const std::string& flags, const std::string& realname);
    std::string endOfWho(const std::string& server, const std::string& nick,
                         const std::string& target);

    std::string join(const std::string& mask, const std::string& channel);
    std::string part(const std::string& mask, const std::string& channel,
                     const std::string& reason);
    std::string quit(const std::string& mask, const std::string& reason);
    std::string nickChange(const std::string& mask, const std::string& new_nick);
    std::string privmsg(const std::string& mask, const std::string& target,
                        const std::string& text);
    std::string notice(const std::string& mask, const std::string& target,
                       const std::string& text);
    std::string kick(const std::string& mask, const std::string& channel,
                     const std::string& target, const std::string& comment);
    std::string invite(const std::string& mask, const std::string& target,
                       const std::string& channel);
    std::string topicChanged(const std::string& mask, const std::string& channel,
                             const std::string& text);
    std::string modeChanged(const std::string& mask, const std::string& channel,
                            const std::string& changes);

    std::string pong(const std::string& server, const std::string& token);
    std::string capabilityList(const std::string& server, const std::string& nick);
    std::string capabilityAck(const std::string& server, const std::string& nick,
                              const std::string& capabilities);
    std::string capabilityNak(const std::string& server, const std::string& nick,
                              const std::string& capabilities);
    std::string error(const std::string& reason);
}

#endif
