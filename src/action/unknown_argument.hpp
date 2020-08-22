#include <stdexcept> // std::runtime_error
#include <string>    // std::string

#ifndef ACTION_UNKNOWN_ARGUMENT_H
#define ACTION_UNKNOWN_ARGUMENT_H

namespace action {

class UnknownArgument : public std::runtime_error {

    public:
        UnknownArgument(const std::string& arg);
};

} // namespace action

#endif
