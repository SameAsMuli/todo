#include "error/empty_argument.hpp"

namespace todo {
namespace error {

EmptyArgument::EmptyArgument(const std::string &method)
    : std::runtime_error("Empty input passed to " + method) {}

} // namespace error
} // namespace todo
