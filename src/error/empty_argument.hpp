#ifndef TODO_ERROR_EMPTY_ARGUMENT_H
#define TODO_ERROR_EMPTY_ARGUMENT_H

#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace todo {
namespace error {

/**
 * @brief Error for receiving no arguments from the user.
 */
class EmptyArgument : public std::runtime_error {

  public:
    /**
     * @brief Error that there was no argument given.
     */
    EmptyArgument(const std::string &method)
        : std::runtime_error("Empty input passed to " + method) {}
};

} // namespace error
} // namespace todo

#endif
