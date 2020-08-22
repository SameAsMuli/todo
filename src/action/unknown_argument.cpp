#include "action/unknown_argument.hpp"

namespace action {

UnknownArgument::UnknownArgument(const std::string& arg):
    std::runtime_error(
            std::string{"Unknown argument: '"} + arg + std::string{"'"})
{ }

} // namespace action
