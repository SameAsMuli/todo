#ifndef TODO_ERROR_INVALID_CONFIG_H
#define TODO_ERROR_INVALID_CONFIG_H

#include <stdexcept> // std::runtime_error
#include <string>    // std::to_string

namespace todo {
namespace error {

/**
 * @brief Error for failing to read a configuration file.
 */
class InvalidConfig : public std::runtime_error {

  public:
    /**
     * @brief Error with the configuration file name and optional description.
     *
     * @param file The name of the malformed configuration file.
     * @param desc An optional description explaining the problem encountered.
     */
    InvalidConfig(const std::string &file, const std::string &desc = "")
        : std::runtime_error("failed to parse file '" + file + "'" +
                             (desc.empty() ? "" : ": " + desc)) {}
};

} // namespace error
} // namespace todo

#endif
