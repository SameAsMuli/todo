#ifndef TODO_UNKNOWN_ARGUMENT_H
#define TODO_UNKNOWN_ARGUMENT_H

#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace todo {

class UnknownArgument : public std::runtime_error {

    public:
        UnknownArgument(const std::string& arg);
};

} // namespace todo

#endif
