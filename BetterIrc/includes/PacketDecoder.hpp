#ifndef PACKETDECODER_HPP
#define PACKETDECODER_HPP

#include <string>
#include <vector>

class PacketDecoder {
    private:
        std::string _prefix;
        std::string _command;
        std::vector<std::string> _params;

        void parse(const std::string& raw_line);

    public:
        PacketDecoder(const std::string& raw_line);
        ~PacketDecoder();

        const std::string& getPrefix() const;
        const std::string& getCommand() const;
        const std::vector<std::string>& getParams() const;
};

#endif