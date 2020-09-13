#ifndef TODO_UNKNOWN_ARGUMENT_H
#define TODO_UNKNOWN_ARGUMENT_H

#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace todo {

/**
 * @brief Error for receiving an unrecognised argument from the user.
 */
class UnknownArgument : public std::runtime_error {

  public:
    /**
     * @brief Error with the name of the unrecognised argument.
     *
     * @param arg The unrecognised argument.
     */
    UnknownArgument(const std::string &arg);
};

} // namespace todo

#endif
