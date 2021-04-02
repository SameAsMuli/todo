#include "error/unknown_option.hpp"

namespace todo {
namespace error {

UnknownOption::UnknownOption(const std::string &option)
    : std::runtime_error("Unknown option: '" + option + "'") {}

} // namespace error
} // namespace todo
