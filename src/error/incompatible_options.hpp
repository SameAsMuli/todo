#ifndef TODO_ERROR_INCOMPATIBLE_OPTIONS_H
#define TODO_ERROR_INCOMPATIBLE_OPTIONS_H

#include <stdexcept> // std::runtime_error

#include "input/option.hpp"

namespace todo {
namespace error {

/**
 * @brief Error for logically inconsistent options.
 */
class IncompatibleOptions : public std::runtime_error {

  public:
    /**
     * @brief Error with the names of the imcompatible options.
     *
     * @param option1 The first incompatible option.
     * @param option2 The second incompatible option.
     */
    IncompatibleOptions(const input::Option &option1,
                        const input::Option &option2)
        : std::runtime_error("options '" + option1.to_string() +
                             "' cannot be used with option '" +
                             option2.to_string() + "'") {}
};

} // namespace error
} // namespace todo

#endif
