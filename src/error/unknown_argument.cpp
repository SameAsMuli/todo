#include "error/unknown_argument.hpp"

namespace todo {
namespace error {

UnknownArgument::UnknownArgument(const std::string &arg)
    : std::runtime_error("Unknown argument: '" + arg + "'") {}

} // namespace error
} // namespace todo
