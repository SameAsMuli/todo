#include <algorithm> // std::find
#include <stdexcept> // std::runtime_error

#include "action/action_abstract.hpp"

namespace todo {
namespace action {

ActionAbstract::ActionAbstract(const std::string &name,
                               const std::string &helpText,
                               const input::Input &input,
                               std::vector<input::OptionType> validOptions,
                               std::optional<unsigned int> argLimit)
    : m_name(name), m_helpText(helpText), m_input(input),
      m_validOptions(validOptions), m_argLimit(argLimit) {}

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

bool ActionAbstract::acceptsOption(const input::OptionType &option) const {
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

    for (input::OptionType option : input.getOptions()) {
        if (!this->acceptsOption(option)) {
            throw std::runtime_error("Option '" + option.toString() +
                                     "' not handled by action: '" +
                                     this->getName() + "'");
        }
    }

    this->run();
}

} // namespace action
} // namespace todo
