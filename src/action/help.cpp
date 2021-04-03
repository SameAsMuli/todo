#include <algorithm> // std::sort
#include <iostream>  // std::cout

#include "action/help.hpp"
#include "error/unknown_argument.hpp"
#include "file/definitions.hpp"
#include "input/option.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace {

bool actionCompare(todo::action::ActionAbstract *a1,
                   todo::action::ActionAbstract *a2) {
    return a1->getName() < a2->getName();
}

} // namespace

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
    std::sort(this->m_actions.begin(), this->m_actions.end(), actionCompare);
}

/*** PRIVATE METHODS ***/

void Help::run() {
    if (!this->getInput().hasActionArg(0)) {
        std::string::size_type maxNameLen = 0;
        std::vector<ActionAbstract *>::size_type minSeparatorLen = 3;

        for (auto const &action : this->m_actions) {
            if (maxNameLen < action->getName().size()) {
                maxNameLen = action->getName().size();
            }
        }

        std::cout << util::display::header() << std::endl;

        std::cout << "TODO Management Utility" << std::endl;
        std::cout << std::endl;

        std::cout << util::display::generalUsage() << std::endl;

        std::cout << std::endl;
        std::cout << util::display::wrap(
                         "If run with no arguments, then any non-archived "
                         "tasks will be printed. All tasks are stored in: '" +
                         std::string(file::getTodoDir(true)) + "'")
                  << std::endl;
        std::cout << std::endl;
        std::cout << "List of actions:" << std::endl;

        for (auto const &action : this->m_actions) {
            std::cout << "  " + action->getName() + " " +
                             std::string(
                                 minSeparatorLen +
                                     (maxNameLen - action->getName().size()),
                                 '.') +
                             " " + action->getHelpText()
                      << std::endl;
        }

        std::cout << util::display::footer() << std::endl;
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
