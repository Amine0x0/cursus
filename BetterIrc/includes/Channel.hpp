#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>

class Channel {
    private:
        std::string _name;
        std::string _topic;
        std::string _key;
        size_t _user_limit;
        bool _invite_only;
        bool _topic_locked;

        std::set<int> _members;
        std::set<int> _operators;
        std::set<int> _invited;

    public:
        Channel();
        Channel(const std::string& name);
        ~Channel();

        const std::string& getName() const;

        void addMember(int client_fd);
        void removeMember(int client_fd);
        bool isMember(int client_fd) const;
        bool isEmpty() const;
        const std::set<int>& getMembers() const;

        void promoteOperator(int client_fd);
        void demoteOperator(int client_fd);
        bool isOperator(int client_fd) const;
        bool hasOperators() const;

        void inviteMember(int client_fd);
        bool isInvited(int client_fd) const;

        const std::string& getTopic() const;
        void setTopic(const std::string& topic);
        bool hasTopic() const;

        void setInviteOnly(bool enabled);
        bool isInviteOnly() const;

        void setTopicLocked(bool enabled);
        bool isTopicLocked() const;

        void setKey(const std::string& key);
        void clearKey();
        bool hasKey() const;
        const std::string& getKey() const;

        void setUserLimit(size_t limit);
        void clearUserLimit();
        bool hasUserLimit() const;
        bool isFull() const;

        std::string getModeFlags() const;
        std::string getModeArguments() const;
};

#endif
