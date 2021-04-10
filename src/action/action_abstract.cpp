#include <algorithm> // std::find
#include <stdexcept> // std::runtime_error

#include "action/action_abstract.hpp"
#include "input/option.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace {

std::unordered_set<input::Option>
includeHelpOption(const std::unordered_set<input::Option> &validOptions) {
    std::unordered_set<input::Option> set{input::Option::help};
    set.insert(validOptions.begin(), validOptions.end());
    return set;
}

} // namespace

namespace todo {
namespace action {

ActionAbstract::ActionAbstract(const std::string &name,
                               const std::string &helpText,
                               const input::Input &input,
                               std::unordered_set<input::Option> validOptions,
                               std::optional<unsigned int> argLimit)
    : m_name(name), m_helpText(helpText), m_input(input),
      m_validOptions(includeHelpOption(validOptions)), m_argLimit(argLimit) {}

bool ActionAbstract::isKnownAs(const std::string &name) const {
    if (this->getName() == name) {
        return true;
    }

    if (std::find(m_aliases.begin(), m_aliases.end(), name) !=
        m_aliases.end()) {
        return true;
    }

    return false;
}

bool ActionAbstract::validOption(const input::Option &option) const {
    return std::find(this->m_validOptions.begin(), this->m_validOptions.end(),
                     option) != this->m_validOptions.end();
}

void ActionAbstract::perform() {
    auto input = this->getInput();

    if (this->getArgLimit().has_value()) {
        if (input.getActionArgCount() > this->getArgLimit()) {
            throw std::runtime_error("Too many arguments for action: '" +
                                     this->getName() + "'");
        }
    }

    for (input::Option option : input.getOptions()) {
        if (!this->validOption(option)) {
            throw std::runtime_error("Option '" + option.toString() +
                                     "' not handled by action: '" +
                                     this->getName() + "'");
        }
    }

    if (input.hasOption(input::Option::help)) {
        this->printDetails();
    } else {
        this->run();
    }
}

void ActionAbstract::printDetails() {
    std::cout << util::display::header() << std::endl;
    std::cout << std::endl;

    auto buffer = this->getName();

    std::cout << "todo " << util::string::toupper(buffer) << " - "
              << this->getHelpText() << std::endl;

    buffer = this->usage();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << buffer << std::endl;
    }

    auto aliases = this->getAliases();
    if (aliases.size() > 0) {
        std::cout << std::endl;
        std::cout << "Aliases:" << std::endl;

        buffer.clear();
        for (auto const &alias : aliases) {
            if (!buffer.empty()) {
                buffer.append(", ");
            }
            buffer.append(alias);
        }
        std::cout << util::display::wrap(buffer) << std::endl;
    }

    buffer = this->description();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << util::display::wrap(buffer) << std::endl;
    }

    std::cout << std::endl;
    std::cout << util::display::footer() << std::endl;
}

} // namespace action
} // namespace todo
