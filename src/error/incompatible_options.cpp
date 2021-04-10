#include <string>

#include "error/incompatible_options.hpp"

namespace todo {
namespace error {

IncompatibleOptions::IncompatibleOptions(const input::Option &option1,
                                         const input::Option &option2)
    : std::runtime_error("Options '" + option1.toString() +
                         "' cannot be used with option '" + option2.toString() +
                         "'") {}

} // namespace error
} // namespace todo
