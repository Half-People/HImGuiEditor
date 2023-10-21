#pragma once

#include <stdexcept>
#include <string>

namespace clipboardxx {

class exception : public std::runtime_error {
public:
    exception(const std::string &reason) : std::runtime_error(reason){};
};

} // namespace clipboardxx
