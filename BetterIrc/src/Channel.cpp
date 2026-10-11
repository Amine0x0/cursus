#include "../includes/Channel.hpp"
#include "../includes/Tooling.hpp"

Channel::Channel()
    : _user_limit(0), _invite_only(false), _topic_locked(false) {}

Channel::Channel(const std::string& name)
    : _name(name), _user_limit(0), _invite_only(false), _topic_locked(false) {}

Channel::~Channel() {}

const std::string& Channel::getName() const { return _name; }

void Channel::addMember(int client_fd) {
    _members.insert(client_fd);
    _invited.erase(client_fd);
}

void Channel::removeMember(int client_fd) {
    _members.erase(client_fd);
    _operators.erase(client_fd);
    _invited.erase(client_fd);
}

bool Channel::isMember(int client_fd) const {
    return _members.find(client_fd) != _members.end();
}

bool Channel::isEmpty() const { return _members.empty(); }

const std::set<int>& Channel::getMembers() const { return _members; }

void Channel::promoteOperator(int client_fd) {
    if (isMember(client_fd)) {
        _operators.insert(client_fd);
    }
}

void Channel::demoteOperator(int client_fd) { _operators.erase(client_fd); }

bool Channel::isOperator(int client_fd) const {
    return _operators.find(client_fd) != _operators.end();
}

void Channel::inviteMember(int client_fd) { _invited.insert(client_fd); }

bool Channel::isInvited(int client_fd) const {
    return _invited.find(client_fd) != _invited.end();
}

const std::string& Channel::getTopic() const { return _topic; }

void Channel::setTopic(const std::string& topic) { _topic = topic; }

bool Channel::hasTopic() const { return !_topic.empty(); }

void Channel::setInviteOnly(bool enabled) { _invite_only = enabled; }

bool Channel::isInviteOnly() const { return _invite_only; }

void Channel::setTopicLocked(bool enabled) { _topic_locked = enabled; }

bool Channel::isTopicLocked() const { return _topic_locked; }

void Channel::setKey(const std::string& key) { _key = key; }

void Channel::clearKey() { _key.clear(); }

bool Channel::hasKey() const { return !_key.empty(); }

const std::string& Channel::getKey() const { return _key; }

void Channel::setUserLimit(size_t limit) { _user_limit = limit; }

void Channel::clearUserLimit() { _user_limit = 0; }

bool Channel::hasOperators() const { return !_operators.empty(); }

bool Channel::hasUserLimit() const { return _user_limit > 0; }

bool Channel::isFull() const {
    return hasUserLimit() && _members.size() >= _user_limit;
}

std::string Channel::getModeFlags() const {
    std::string flags = "+";

    if (_invite_only) { flags += "i"; }
    if (_topic_locked) { flags += "t"; }
    if (hasKey()) { flags += "k"; }
    if (hasUserLimit()) { flags += "l"; }
    return flags;
}

std::string Channel::getModeArguments() const {
    std::string arguments;

    if (hasKey()) { arguments += " " + _key; }
    if (hasUserLimit()) { arguments += " " + tooling::toString(_user_limit); }
    return arguments;
}
