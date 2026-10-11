#ifndef SESSION_HPP
#define SESSION_HPP

#include <string>
#include <bitset>

class Session {
    private:
        std::string _raw_buffer;
        std::string _out_buffer;
        
        static const size_t IDX_PASS = 0;
        static const size_t IDX_NICK = 1;
        static const size_t IDX_USER = 2;
        static const size_t PassCondition = 3;

        std::string _nickname;
        std::string _username;
        std::string _realname;
        std::string _hostname;

        std::bitset<PassCondition> _reg_flags;

        bool _welcome_sent;
        bool _should_disconnect;

    public:
        Session();
        ~Session();

        void setPassDone();
        void setNickDone();
        void setUserDone();
        bool isPassDone() const;
        bool isNickDone() const;
        bool isUserDone() const;
        bool isRegistered() const;

        std::string& getBuffer();
        void appendBuffer(const std::string& data);
        void clearBuffer();

        std::string& getOutput();
        void queueOutput(const std::string& data);
        bool hasPendingOutput() const;

        void markWelcomeSent();
        bool isWelcomeSent() const;

        void markForDisconnect();
        bool shouldDisconnect() const;

        void setNick(const std::string& nick) { _nickname = nick; }
        const std::string& getNick() const { return _nickname; }
        void setUser(const std::string& user, const std::string& real) { _username = user; _realname = real; }
        const std::string& getUser() const { return _username; }
        const std::string& getRealName() const { return _realname; }
        void setHostname(const std::string& host) { _hostname = host; }
        const std::string& getHostname() const { return _hostname; }

        std::string getMask() const;
};

#endif
