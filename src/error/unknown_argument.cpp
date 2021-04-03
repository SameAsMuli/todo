#include "error/unknown_argument.hpp"

namespace todo {
namespace error {

UnknownArgument::UnknownArgument(const std::string &arg,
                                 const std::string &type)
    : std::runtime_error("Unknown " + type + ": '" + arg + "'") {}

} // namespace error
} // namespace todo
