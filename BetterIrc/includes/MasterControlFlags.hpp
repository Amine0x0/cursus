#ifndef MasterControlFlags_HPP
#define MasterControlFlags_HPP

#include <string>
#include <cstddef>

#define DEV_MODE 1

const std::string __ServerName = "DebugServer";
const std::string __ServerVersion = "1.0";

const std::string __UserModes = "o";
const std::string __ChannelModes = "itkol";

const size_t __MaxNickLength = 30;
const size_t __ReadBufferSize = 4096;

const size_t __MaxPendingInput = 8192;
const size_t __MaxPendingOutput = 1024 * 1024;

#endif
