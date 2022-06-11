#ifndef TODO_ERROR_UNKNOWN_ARGUMENT_H
#define TODO_ERROR_UNKNOWN_ARGUMENT_H

#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace todo {
namespace error {

/**
 * @brief Error for receiving an unrecognised argument from the user.
 */
class UnknownArgument : public std::runtime_error {

  public:
    /**
     * @brief Error with the name of the unrecognised argument.
     *
     * @param arg The unrecognised argument.
     * @param type The type name of the argument. Defaults to "argument".
     */
    UnknownArgument(const std::string &arg,
                    const std::string &type = "argument")
        : std::runtime_error("Unknown " + type + ": '" + arg + "'") {}
};

} // namespace error
} // namespace todo

#endif
