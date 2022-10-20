#include <algorithm> // std::find, std::sort
#include <stdexcept> // std::runtime_error
#include <string>    // std::string
#include <vector>    // std::vector

#include "action/action_abstract.hpp"
#include "input/option.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace {

bool string_compare(std::string s1, std::string s2) { return s1 < s2; }

bool option_compare(input::Option o1, input::Option o2) {
    return string_compare(o1.to_string(), o2.to_string());
}

void print_aliases(const todo::action::ActionAbstract *action) {
    auto unsortedAliases = action->get_aliases();
    if (unsortedAliases.size() > 0) {
        std::cout << std::endl;
        std::cout << "Aliases:" << std::endl;

        /* Make sure the aliases are in alphabetical order */
        std::vector<std::string> aliases;
        aliases.insert(aliases.end(), unsortedAliases.begin(),
                       unsortedAliases.end());
        std::sort(aliases.begin(), aliases.end(), string_compare);

        std::string buffer;
        for (const auto &alias : aliases) {
            if (buffer.empty()) {
                buffer.append(util::display::INDENT);
            } else {
                buffer.append(", ");
            }
            buffer.append(alias);
        }
        std::cout << util::display::wrap(buffer, util::display::WIDTH)
                  << std::endl;
    }
}

void print_valid_options(const todo::action::ActionAbstract *action) {
    auto unsortedOptions = action->get_valid_options();
    if (unsortedOptions.size() > 0) {
        std::cout << std::endl;
        std::cout << "Valid options:" << std::endl;

        /* Make sure the options are in alphabetical order */
        std::string::size_type maxOptionStringLen = 0;
        std::string::size_type minSeparatorLen = 1;

        for (const auto &option : unsortedOptions) {
            auto fullString = option.get_full_string();
            if (maxOptionStringLen < fullString.size()) {
                maxOptionStringLen = fullString.size();
            }
        }

        std::vector<input::Option> options;
        options.insert(options.end(), unsortedOptions.begin(),
                       unsortedOptions.end());
        std::sort(options.begin(), options.end(), option_compare);

        for (const auto &option : options) {
            auto optionString = option.get_full_string();
            std::cout << util::display::INDENT + optionString + " " +
                             std::string(
                                 minSeparatorLen +
                                     (maxOptionStringLen - optionString.size()),
                                 ' ') +
                             " " + option.get_description()
                      << std::endl;
        }
    }
}

} // namespace

namespace todo {
namespace action {

ActionAbstract::ActionAbstract(const std::string &name,
                               const std::string &helpText,
                               std::optional<unsigned int> argLimit)
    : m_name(name), m_helpText(helpText), m_argLimit(argLimit) {
    this->add_valid_option(input::Option::help);
}

void ActionAbstract::add_alias(const std::string &alias) {
    m_aliases.insert(alias);
}

bool ActionAbstract::is_known_as(const std::string &name) const {
    if (this->get_name() == name) {
        return true;
    }

    if (std::find(m_aliases.begin(), m_aliases.end(), name) !=
        m_aliases.end()) {
        return true;
    }

    return false;
}

void ActionAbstract::add_valid_option(const input::Option &option) {
    m_validOptions.insert(option);
}

bool ActionAbstract::valid_option(const input::Option &option) const {
    return std::find(this->m_validOptions.begin(), this->m_validOptions.end(),
                     option) != this->m_validOptions.end();
}

void ActionAbstract::perform(const input::Input &input) {
    if (this->get_arg_limit().has_value()) {
        if (input.get_action_arg_count() > this->get_arg_limit()) {
            throw std::runtime_error("too many arguments for action: '" +
                                     this->get_name() + "'");
        }
    }

    for (input::Option option : input.get_options()) {
        if (!this->valid_option(option)) {
            throw std::runtime_error("option '" + option.to_string() +
                                     "' not handled by action: '" +
                                     this->get_name() + "'");
        }
    }

    if (input.has_option(input::Option::help)) {
        this->print_details();
    } else {
        this->run(input);
    }
}

void ActionAbstract::print_details() const {
    std::cout << util::display::header() << std::endl;
    std::cout << std::endl;

    auto buffer = this->get_name();

    std::cout << "todo " << util::string::toupper(buffer) << " - "
              << this->get_help_text() << std::endl;

    buffer = this->usage();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << buffer << std::endl;
    }

    print_aliases(this);

    print_valid_options(this);

    buffer = this->description();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << util::display::wrap(buffer, util::display::WIDTH)
                  << std::endl;
    }

    std::cout << std::endl;
    std::cout << util::display::footer() << std::endl;
}

} // namespace action
} // namespace todo
