#include "todo/unknown_argument.hpp"

namespace todo {

UnknownArgument::UnknownArgument(const std::string& arg):
    std::runtime_error("Unknown argument: '" + arg + "'")
{ }

} // namespace todo
