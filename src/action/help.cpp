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

Help::Help(input::Input input)
    : ActionAbstract("help", "Display this help text", input,
                     {input::Option::help}, 1) {
    this->addAlias("--help");
}

std::string Help::description() const {
    return "If run with no arguments, then general information about the "
           "program will be shown. If passed an action as an argument, then "
           "detailed information on that specific action will be shown.";
}

std::string Help::usage() const { return "usage: todo help [action]"; }

void Help::addActions(std::vector<ActionAbstract *> &actions) {
    this->m_actions = actions;
}

/*** PRIVATE METHODS ***/

void Help::run() {
    if (!this->getInput().hasActionArg(0)) {
        std::vector<std::pair<std::string, std::string>> actions;

        for (auto const &action : this->m_actions) {
            actions.push_back({action->getName(), action->getHelpText()});
        }

        std::cout << util::display::programOverview(actions) << std::endl;
    } else {
        auto actionName = this->getInput().getActionArg(0);
        for (auto const &action : this->m_actions) {
            if (action->getName() == actionName) {
                this->printDetails();
                break;
            }
        }

        throw error::UnknownArgument(actionName, "action");
    }
}

} // namespace action
} // namespace todo
