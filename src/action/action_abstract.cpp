#include <algorithm> // std::find
#include <stdexcept> // std::runtime_error

#include "action/action_abstract.hpp"

namespace todo {
namespace action {

ActionAbstract::ActionAbstract(const std::string &name,
                               const std::string &helpText,
                               const util::Input &input,
                               std::optional<unsigned int> argLimit)
    : m_name(name), m_helpText(helpText), m_input(input), m_argLimit(argLimit) {
}

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

void ActionAbstract::perform() {
    if (this->getArgLimit().has_value()) {
        // Subtract 1 so as not to count the action itself
        if (this->getInput().size() - util::Input::PARAM_START_INDEX >
            this->getArgLimit()) {
            throw std::runtime_error("Too many arguments for action: '" +
                                     this->getName() + "'");
        }
    }

    this->run();
}

} // namespace action
} // namespace todo
