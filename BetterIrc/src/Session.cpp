#include "../includes/Session.hpp"

Session::Session()
    : _raw_buffer(""), _out_buffer(""), _reg_flags(0),
      _welcome_sent(false), _should_disconnect(false) {}

Session::~Session() {}

void Session::setPassDone() {
    _reg_flags.set(IDX_PASS);
}

void Session::setNickDone() {
    _reg_flags.set(IDX_NICK);
}

void Session::setUserDone() {
    _reg_flags.set(IDX_USER);
}

bool Session::isPassDone() const {
    return _reg_flags.test(IDX_PASS);
}

bool Session::isNickDone() const {
    return _reg_flags.test(IDX_NICK);
}

bool Session::isUserDone() const {
    return _reg_flags.test(IDX_USER);
}

bool Session::isRegistered() const {
    return _reg_flags.count() == PassCondition;
}

std::string& Session::getBuffer() {
    return _raw_buffer;
}

void Session::appendBuffer(const std::string& data) {
    _raw_buffer.append(data);
}

void Session::clearBuffer() {
    _raw_buffer.clear();
}

std::string& Session::getOutput() {
    return _out_buffer;
}

void Session::queueOutput(const std::string& data) {
    _out_buffer.append(data);
}

bool Session::hasPendingOutput() const {
    return !_out_buffer.empty();
}

void Session::markWelcomeSent() {
    _welcome_sent = true;
}

bool Session::isWelcomeSent() const {
    return _welcome_sent;
}

void Session::markForDisconnect() {
    _should_disconnect = true;
}

bool Session::shouldDisconnect() const {
    return _should_disconnect;
}

std::string Session::getMask() const {
    return _nickname + "!" + _username + "@" + _hostname;
}
