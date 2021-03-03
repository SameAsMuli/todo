#include <algorithm> // std::sort
#include <iostream>  // std::cout

#include "action/help.hpp"
#include "file/definitions.hpp"
#include "util/string.hpp"

namespace {

// TODO-SAM Use min of this and console width
static int MAX_WIDTH = 50;

std::string footer() { return "Written by Sam Amis"; }

std::string wrap(const std::string &input) {
    return util::string::wrap(input, MAX_WIDTH);
}

void printActionDetails(todo::action::ActionAbstract *const action) {
    auto buffer = action->getName();

    std::cout << "todo " << util::string::toupper(buffer) << " - "
              << action->getHelpText() << std::endl;

    buffer = action->usage();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << buffer << std::endl;
    }

    auto aliases = action->getAliases();
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
        std::cout << wrap(buffer) << std::endl;
    }

    buffer = action->description();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << wrap(buffer) << std::endl;
    }

    std::cout << std::endl;
    std::cout << footer() << std::endl;
}

} // namespace

namespace todo {
namespace action {

Help::Help(util::Input input)
    : ActionAbstract("help", "Display this help text", input, 1) {
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

void Help::printGeneralUsage() const {
    std::cout << "usage: todo [action] [--option] [<argument>]" << std::endl;
    std::cout << "            [--help] [<action>]" << std::endl;
}

/*** PRIVATE METHODS ***/

void Help::run() {
    if (this->getInput().hasOption(util::Input::PARAM_START_INDEX)) {
        auto actionName =
            this->getInput().getOption(util::Input::PARAM_START_INDEX);

        for (auto const &action : this->m_actions) {
            if (action->getName() == actionName) {
                printActionDetails(action);
                break;
            }
        }
    } else {
        std::string::size_type maxNameLen = 0;
        std::vector<ActionAbstract *>::size_type minSeparatorLen = 3;

        for (auto const &action : this->m_actions) {
            if (maxNameLen < action->getName().size()) {
                maxNameLen = action->getName().size();
            }
        }

        std::cout << "TODO Management Utility" << std::endl;
        std::cout << std::endl;

        printGeneralUsage();

        std::cout << std::endl;
        std::cout << wrap("If run with no arguments, then any non-archived "
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

        std::cout << std::endl;
        std::cout << footer() << std::endl;
    }
}

bool Help::actionCompare(ActionAbstract *a1, ActionAbstract *a2) {
    return a1->getName() < a2->getName();
}

} // namespace action
} // namespace todo
