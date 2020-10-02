#include "todo/empty_argument.hpp"

namespace todo {

EmptyArgument::EmptyArgument(const std::string &method)
    : std::runtime_error("Empty input passed to " + method) {}

} // namespace todo
