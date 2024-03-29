#ifndef TODO_ERROR_UNKNOWN_OPTION_H
#define TODO_ERROR_UNKNOWN_OPTION_H

#include <stdexcept> // std::runtime_error
#include <string>    // std::string

namespace todo {
namespace error {

/**
 * @brief Error for receiving an unrecognised option from the user.
 */
class UnknownOption : public std::runtime_error {

  public:
    /**
     * @brief Error with the name of the unrecognised option.
     *
     * @param option The unrecognised option.
     */
    UnknownOption(const std::string &option);
};

} // namespace error
} // namespace todo

#endif
