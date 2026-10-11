#include "../includes/PacketDecoder.hpp"

PacketDecoder::PacketDecoder(const std::string& raw_line) {
    parse(raw_line);
}

PacketDecoder::~PacketDecoder() {}

void PacketDecoder::parse(const std::string& raw_line) {
    if (raw_line.empty()) return;

    size_t idx = 0;

    if (raw_line[0] == ':') {
        size_t space_pos = raw_line.find(' ');
        if (space_pos != std::string::npos) {
            _prefix = raw_line.substr(1, space_pos - 1);
            idx = space_pos + 1;
        } else {
            return;
        }
    }

    while (idx < raw_line.length() && raw_line[idx] == ' ') {
        idx++;
    }

    size_t cmd_end = raw_line.find(' ', idx);
    if (cmd_end == std::string::npos) {
        _command = raw_line.substr(idx);
        return;
    } else {
        _command = raw_line.substr(idx, cmd_end - idx);
        idx = cmd_end + 1;
    }

    while (idx < raw_line.length()) {
        while (idx < raw_line.length() && raw_line[idx] == ' ') {
            idx++;
        }
        if (idx >= raw_line.length()) break;

        if (raw_line[idx] == ':') {
            _params.push_back(raw_line.substr(idx + 1));
            break;
        } else {
            size_t param_end = raw_line.find(' ', idx);
            if (param_end == std::string::npos) {
                _params.push_back(raw_line.substr(idx));
                break;
            } else {
                _params.push_back(raw_line.substr(idx, param_end - idx));
                idx = param_end + 1;
            }
        }
    }
}

const std::string& PacketDecoder::getPrefix() const { return _prefix; }
const std::string& PacketDecoder::getCommand() const { return _command; }
const std::vector<std::string>& PacketDecoder::getParams() const { return _params; }