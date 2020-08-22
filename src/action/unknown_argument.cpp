#include "action/unknown_argument.hpp"

namespace action {

UnknownArgument::UnknownArgument(const std::string& arg):
    std::runtime_error("Unknown argument: '" + arg + "'")
{ }

} // namespace action
