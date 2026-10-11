#include "../includes/Server.hpp"
#include "../includes/Tooling.hpp"
#include "../includes/Replies.hpp"
#include "../includes/Signals.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

Server::Server(int port, const std::string& password) {
    PrintAsciiBanner();
    this->_metadata.start_time = std::time(NULL);
    this->_metadata.port = port;
    this->_metadata._active_connections = 0;
    this->_metadata._servername = __ServerName;
    this->_listen_fd = -1;
    this->_password = password;

    _function_pool.push_back(&Server::setupSocket);
    _function_pool.push_back(&Server::setupSocketOptions);
    _function_pool.push_back(&Server::setupNonBlocking);
    _function_pool.push_back(&Server::setupBind);
    _function_pool.push_back(&Server::setupListen);
    _function_pool.push_back(&Server::setupPoll);

    registerCommands();

    this->_is_ready = runFunctionPool();
    if (this->_is_ready) {
        ServerLog(Server::INIT_MSG);
    } else {
        tooling::PrettyLog(LOG_ERROR, "[IRC] Fatal: Server initialization failed.");
    }
}

Server::~Server(){
    bool listen_fd_closed = false;
    for (size_t i = 0; i < this->_fds.size(); ++i) {
        if (this->_fds[i].fd >= 0) {
            if (this->_fds[i].fd == this->_listen_fd) {
                listen_fd_closed = true;
            }
            close(this->_fds[i].fd);
        }
    }
    if (this->_listen_fd >= 0 && !listen_fd_closed) {
        close(this->_listen_fd);
    }
    ServerLog(Server::DESTRUCTION_MSG);
}

bool Server::isReady() const {
    return this->_is_ready;
}

bool Server::setupSocket() {
    tooling::PrettyLog(LOG_INFO, "setting up socket with [AF_INET] [SOCK_STREAM]...");
    this->_listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    return (this->_listen_fd >= 0);
}

bool Server::setupSocketOptions() {
    tooling::PrettyLog(LOG_INFO, "setting up socket options [opt = 1]");
    int opt = 1;
    return (setsockopt(this->_listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == 0);
}

bool Server::setupNonBlocking() {
    tooling::PrettyLog(LOG_INFO, "enabling NonBlocking");
    return (fcntl(this->_listen_fd, F_SETFL, O_NONBLOCK) >= 0);
}

bool Server::setupBind() {
    std::stringstream ss;
    ss << "binding port " << this->_metadata.port;
    tooling::PrettyLog(LOG_INFO, ss.str());
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(this->_metadata.port);

    return (bind(this->_listen_fd, (struct sockaddr*)&address, sizeof(address)) >= 0);
}

bool Server::setupListen() {
    tooling::PrettyLog(LOG_INFO, "calling listen() syscall");
    return (listen(this->_listen_fd, SOMAXCONN) >= 0);
}

bool Server::setupPoll() {
    tooling::PrettyLog(LOG_INFO, "setting up Poll");
    struct pollfd pfd;
    pfd.fd = this->_listen_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    this->_fds.push_back(pfd);
    return true;
}

bool Server::runFunctionPool() {
    tooling::PrettyLog(LOG_INFO, "running function pool");
    for (std::vector<ServerRoutine>::iterator it = _function_pool.begin(); it != _function_pool.end(); ++it) {
        if (!(this->**it)()) {
            return false;
        }
    }
    if (this->_listen_fd < 0 || this->_fds.empty()) {
        return false;
    }
    return true;
}

void Server::registerCommands() {
    tooling::PrettyLog(LOG_INFO, "registering command pool");

    _command_pool["PASS"] = &Server::cmdPass;
    _command_pool["NICK"] = &Server::cmdNick;
    _command_pool["USER"] = &Server::cmdUser;
    _command_pool["QUIT"] = &Server::cmdQuit;
    _command_pool["PING"] = &Server::cmdPing;
    _command_pool["PONG"] = &Server::cmdPong;
    _command_pool["CAP"] = &Server::cmdCap;

    _command_pool["PRIVMSG"] = &Server::cmdPrivmsg;
    _command_pool["NOTICE"] = &Server::cmdNotice;

    _command_pool["JOIN"] = &Server::cmdJoin;
    _command_pool["WHO"] = &Server::cmdWho;
    _command_pool["PART"] = &Server::cmdPart;
    _command_pool["TOPIC"] = &Server::cmdTopic;
    _command_pool["INVITE"] = &Server::cmdInvite;
    _command_pool["KICK"] = &Server::cmdKick;
    _command_pool["MODE"] = &Server::cmdMode;
}

void Server::ServerLog(const Server::ServerMsg msg){
    switch(msg){
        case Server::INIT_MSG:
            tooling::PrettyLog(LOG_INFO, "[IRC] Server initialized."); 
            break;
        case Server::DESTRUCTION_MSG:
            tooling::PrettyLog(LOG_INFO, "[IRC] Server Ressources deallocated.");
            #if DEV_MODE
                QuitServerDump();
            #endif
            break;
        case Server::RUNNING_MSG:
            tooling::PrettyLog(LOG_SUCCESS, "[IRC] Server is listening...");
            #if DEV_MODE
                ServerStatsDbg();
            #endif
            break;
        default:
            tooling::PrettyLog(LOG_ERROR, "unknown logs from server");
            break;
    }
}

Server::Metadata Server::run(){
    ServerLog(Server::RUNNING_MSG);

    while (!signals::stopRequested()) {
        int activity = poll(&this->_fds[0], this->_fds.size(), -1);

        if (activity < 0) {
            break;
        }

        if (activity == 0) continue;

        size_t polled_count = this->_fds.size();
        for (size_t i = 0; i < polled_count; ++i) {
            const int event_fd = this->_fds[i].fd;
            const short revents = this->_fds[i].revents;

            if (revents == 0) continue;

            if (event_fd == this->_listen_fd) {
                if (revents & POLLIN) {
                    handleNewConnection();
                }
                continue;
            }

            if (revents & POLLIN) {
                handleClientData(event_fd);
            }
            if (revents & POLLOUT) {
                flushClientOutput(event_fd);
            }
            if (revents & (POLLHUP | POLLERR | POLLNVAL)) {
                Session& session = getSession(event_fd);
                session.getOutput().clear();
                session.markForDisconnect();
            }
        }

        reapClosedSessions();
    }

    this->_metadata._active_connections = this->_sessions.size();
    return this->_metadata;
}

void Server::handleNewConnection() {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(this->_listen_fd, (struct sockaddr*)&client_addr, &client_len);
    
    if (client_fd >= 0) {
        if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0) {
            close(client_fd);
            tooling::PrettyLog(LOG_ERROR, "[IRC] Failed to enable nonblocking client socket.");
            return;
        }
        
        struct pollfd client_pfd;
        client_pfd.fd = client_fd;
        client_pfd.events = POLLIN;
        client_pfd.revents = 0;
        this->_fds.push_back(client_pfd);
        
        this->_sessions[client_fd] = Session();
        this->_sessions[client_fd].setHostname(inet_ntoa(client_addr.sin_addr));
        tooling::PrettyLog(LOG_SUCCESS, "[IRC] New client connected.");
    }
}

void Server::handleClientData(int client_fd) {
    char buffer[__ReadBufferSize];
    int bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read == 0) {
        getSession(client_fd).markForDisconnect();
        return;
    }

    if (bytes_read < 0) {
        return;
    }

    buffer[bytes_read] = '\0';

    Session& session = getSession(client_fd);
    session.appendBuffer(buffer);

    std::string& raw_buff = session.getBuffer();
    size_t pos;
    while ((pos = raw_buff.find('\n')) != std::string::npos) {
        std::string line = raw_buff.substr(0, pos);
        raw_buff.erase(0, pos + 1);

        if (!line.empty() && line[line.length() - 1] == '\r') {
            line.erase(line.length() - 1);
        }
        if (line.empty()) continue;

        PacketDecoder decoder(line);

        std::stringstream ss;
        ss << "[IRC] Cmd: " << decoder.getCommand() << " | Params: " << decoder.getParams().size();
        tooling::PrettyLog(LOG_INFO, ss.str());

        executeCommand(client_fd, decoder);

        if (session.shouldDisconnect()) break;
    }

    if (raw_buff.length() > __MaxPendingInput) {
        queueMessage(client_fd, replies::error("Request too long"));
        session.markForDisconnect();
    }
}

void Server::executeCommand(int client_fd, const PacketDecoder& decoder) {
    if (decoder.getCommand().empty()) return;

    const std::string command = tooling::toUpper(decoder.getCommand());
    Session& session = getSession(client_fd);

    std::map<std::string, CommandRoutine>::const_iterator entry = _command_pool.find(command);
    if (entry == _command_pool.end()) {
        queueMessage(client_fd, replies::unknownCommand(getServerName(), session.getNick(), command));
        return;
    }

    if (requiresRegistration(command) && !session.isRegistered()) {
        queueMessage(client_fd, replies::notRegistered(getServerName(), session.getNick()));
        return;
    }

    (this->*(entry->second))(client_fd, decoder);
}

bool Server::requiresRegistration(const std::string& command) const {
    return !(command == "PASS" || command == "NICK" || command == "USER" ||
             command == "QUIT" || command == "PING" || command == "PONG" ||
             command == "CAP");
}

#if DEV_MODE
void Server::QuitServerDump() const{
    const time_t current_time = std::time(NULL);
    const time_t current_uptime = current_time - this->_metadata.start_time;

    tooling::PrettyLog(LOG_DEV, "[DEV] --- Server State before leaving ---");

    std::stringstream summary;
    summary << "port: " << this->_metadata.port
            << ", uptime: " << current_uptime << " seconds"
            << ", poll entries: " << this->_fds.size()
            << ", sessions: " << this->_sessions.size()
            << ", channels: " << this->_channels.size();
    tooling::PrettyLog(LOG_DEV, summary.str());

    for (std::map<int, Session>::const_iterator session = this->_sessions.begin();
         session != this->_sessions.end(); ++session) {
        std::stringstream session_info;
        session_info << "session fd: " << session->first
                     << ", nick: " << (session->second.getNick().empty()
                         ? "<unregistered>" : session->second.getNick())
                     << ", registered: "
                     << (session->second.isRegistered() ? "yes" : "no")
                     << ", pending output: "
                     << (session->second.hasPendingOutput() ? "yes" : "no");
        tooling::PrettyLog(LOG_DEV, session_info.str());
    }

    for (std::map<std::string, Channel>::const_iterator channel = this->_channels.begin();
         channel != this->_channels.end(); ++channel) {
        size_t operator_count = 0;
        const std::set<int>& members = channel->second.getMembers();
        for (std::set<int>::const_iterator member = members.begin();
             member != members.end(); ++member) {
            if (channel->second.isOperator(*member)) {
                ++operator_count;
            }
        }

        std::stringstream channel_info;
        channel_info << "channel: " << channel->second.getName()
                     << ", members: " << members.size()
                     << ", operators: " << operator_count;
        tooling::PrettyLog(LOG_DEV, channel_info.str());
    }
}

void Server::ServerStatsDbg() const {
    time_t current_uptime = std::time(NULL) - this->_metadata.start_time;

    std::tm* timeinfo = std::localtime(&this->_metadata.start_time);
    
    std::string time_str = std::asctime(timeinfo);
    
    if (!time_str.empty() && time_str[time_str.length() - 1] == '\n') {
        time_str.erase(time_str.length() - 1);
    }

    tooling::PrettyLog(LOG_DEV, "[DEV] --- Server Stat Dump ---");
    
    std::stringstream ss1, ss2, ss3, ss4, ss5;
    ss1 << "port: " << this->_metadata.port;
    ss2 << "server started at: " << time_str;
    ss3 << "uptime: " << current_uptime << " seconds";
    ss4 << "active connections: " << this->_metadata._active_connections << " connections.";
    ss5 << "server name: " << "[" << this->_metadata._servername << "]";

    tooling::PrettyLog(LOG_DEV, ss1.str());
    tooling::PrettyLog(LOG_DEV, ss2.str());
    tooling::PrettyLog(LOG_DEV, ss3.str());
    tooling::PrettyLog(LOG_DEV, ss4.str());
    tooling::PrettyLog(LOG_DEV, ss5.str());
}
#endif
