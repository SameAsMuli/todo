#include <iostream> // std::cout
#include <utility>  // std::pair

#include "action/help.hpp"
#include "error/unknown_argument.hpp"
#include "file/definitions.hpp"
#include "input/option.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace todo {
namespace action {

Help::Help() : ActionAbstract("help", "Display this help text", 1) {}

std::string Help::description() const {
    return "If run with no arguments, then general information about the "
           "program will be shown. If passed an action as an argument, then "
           "detailed information on that specific action will be shown.";
}

std::string Help::usage() const {
    return "usage: todo " + this->getName() + " [<action>]";
}

void Help::addActions(std::vector<ActionAbstract *> &actions) {
    this->m_actions = actions;
}

/*** PRIVATE METHODS ***/

void Help::run(const input::Input &input) {
    if (!input.hasActionArg(0)) {
        std::vector<std::pair<std::string, std::string>> actions;

        for (auto const &action : this->m_actions) {
            actions.push_back({action->getName(), action->getHelpText()});
        }

        std::cout << util::display::programOverview(actions) << std::endl;
    } else {
        auto actionName = input.getActionArg(0);
        for (auto const &action : this->m_actions) {
            if (action->getName() == actionName) {
                action->printDetails();
                return;
            }
        }

        throw error::UnknownArgument(actionName, "action");
    }
}

} // namespace action
} // namespace todo
