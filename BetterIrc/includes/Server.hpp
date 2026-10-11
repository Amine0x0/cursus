#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <ctime>
#include <poll.h>
#include "../includes/Tooling.hpp"
#include "../includes/Session.hpp"
#include "../includes/Channel.hpp"
#include "../includes/MasterControlFlags.hpp"
#include "../includes/PacketDecoder.hpp"

class Server{
    private:
        enum ServerMsg{
            INIT_MSG,
            DESTRUCTION_MSG,
            RUNNING_MSG,
        };

        struct Metadata{
            size_t _active_connections;
            time_t start_time; 
            time_t uptime;
            std::string _servername;
            int port;
        };

        int _listen_fd;
        bool _is_ready;
        std::string _password;
        Metadata _metadata;
        std::vector<struct pollfd> _fds;
        std::map<int, Session> _sessions;
        std::map<std::string, Channel> _channels;

        typedef bool (Server::*ServerRoutine)();
        std::vector<ServerRoutine> _function_pool;

        typedef void (Server::*CommandRoutine)(int, const PacketDecoder&);
        std::map<std::string, CommandRoutine> _command_pool;

        bool setupSocket();
        bool setupSocketOptions();
        bool setupNonBlocking();
        bool setupBind();
        bool setupListen();
        bool setupPoll();
        bool runFunctionPool();
        void registerCommands();

        void handleNewConnection();
        void handleClientData(int client_fd);
        void flushClientOutput(int client_fd);
        void reapClosedSessions();
        void closeSession(int client_fd);

        struct pollfd* findPollEntry(int client_fd);
        void queueMessage(int client_fd, const std::string& message);
        void queueToChannel(const Channel& channel, const std::string& message, int except_fd);
        void queueToPeers(int client_fd, const std::string& message, bool include_self);

        const std::string& getServerName() const;
        Session& getSession(int client_fd);
        int findFdByNick(const std::string& nick);
        Channel* findChannel(const std::string& name);

        void executeCommand(int client_fd, const PacketDecoder& decoder);
        bool requiresRegistration(const std::string& command) const;

        void cmdPass(int client_fd, const PacketDecoder& decoder);
        void cmdNick(int client_fd, const PacketDecoder& decoder);
        void cmdUser(int client_fd, const PacketDecoder& decoder);
        void cmdQuit(int client_fd, const PacketDecoder& decoder);
        void cmdPing(int client_fd, const PacketDecoder& decoder);
        void cmdPong(int client_fd, const PacketDecoder& decoder);
        void cmdCap(int client_fd, const PacketDecoder& decoder);
        void completeRegistration(int client_fd);
        void removeSessionFromChannels(int client_fd, const std::string& quit_reason);

        void cmdPrivmsg(int client_fd, const PacketDecoder& decoder);
        void cmdNotice(int client_fd, const PacketDecoder& decoder);
        void deliverMessage(int client_fd, const PacketDecoder& decoder, bool is_notice);

        void cmdJoin(int client_fd, const PacketDecoder& decoder);
        void cmdWho(int client_fd, const PacketDecoder& decoder);
        void cmdPart(int client_fd, const PacketDecoder& decoder);
        void cmdTopic(int client_fd, const PacketDecoder& decoder);
        void cmdInvite(int client_fd, const PacketDecoder& decoder);
        void cmdKick(int client_fd, const PacketDecoder& decoder);
        void joinChannel(int client_fd, const std::string& name, const std::string& key);
        void sendChannelEntry(int client_fd, const Channel& channel);

        void cmdMode(int client_fd, const PacketDecoder& decoder);
        void applyChannelModes(int client_fd, Channel& channel, const PacketDecoder& decoder);
        bool applyInviteOnly(Channel& channel, bool adding);
        bool applyTopicLock(Channel& channel, bool adding);
        bool applyChannelKey(int client_fd, Channel& channel, bool adding, const std::string& argument);
        bool applyOperator(int client_fd, Channel& channel, bool adding, const std::string& argument);
        bool applyUserLimit(Channel& channel, bool adding, const std::string& argument);

    public:
        Server(int port, const std::string& password);
        ~Server();

        bool isReady() const;
        void ServerLog(const ServerMsg msg);
        #if DEV_MODE
            void ServerStatsDbg() const;
            void QuitServerDump() const;
        #endif

        Metadata run();
};

#endif
