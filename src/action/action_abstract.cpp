#include <algorithm> // std::find, std::sort
#include <stdexcept> // std::runtime_error
#include <string>    // std::string
#include <vector>    // std::vector

#include "action/action_abstract.hpp"
#include "input/option.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace {

bool stringCompare(std::string s1, std::string s2) { return s1 < s2; }

} // namespace

namespace todo {
namespace action {

ActionAbstract::ActionAbstract(const std::string &name,
                               const std::string &helpText,
                               const input::Input &input,
                               std::optional<unsigned int> argLimit)
    : m_name(name), m_helpText(helpText), m_input(input), m_argLimit(argLimit) {
    this->addValidOption(input::Option::help);
}

void ActionAbstract::addAlias(const std::string &alias) {
    m_aliases.insert(alias);
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

void ActionAbstract::addValidOption(const input::Option &option) {
    m_validOptions.insert(option);
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

    auto unsortedOptions = this->getValidOptions();
    if (unsortedOptions.size() > 0) {
        std::cout << std::endl;
        std::cout << "Valid options:" << std::endl;

        /* Make sure the options are in alphabetical order */
        std::vector<std::string> options;
        for (auto const &option : unsortedOptions) {
            if (option.hasCharRepresentation()) {
                options.push_back(option.toString() + ", -" +
                                  option.getCharRepresentation());
            } else {
                options.push_back(option.toString());
            }
        }

        std::sort(options.begin(), options.end(), stringCompare);

        for (auto const &optionString : options) {
            std::cout << util::display::INDENT << optionString << std::endl;
        }
    }

    auto unsortedAliases = this->getAliases();
    if (unsortedAliases.size() > 0) {
        std::cout << std::endl;
        std::cout << "Aliases:" << std::endl;

        /* Make sure the aliases are in alphabetical order */
        std::vector<std::string> aliases;
        aliases.insert(aliases.end(), unsortedAliases.begin(),
                       unsortedAliases.end());
        std::sort(aliases.begin(), aliases.end(), stringCompare);

        buffer.clear();
        for (auto const &alias : aliases) {
            if (buffer.empty()) {
                buffer.append(util::display::INDENT);
            } else {
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
