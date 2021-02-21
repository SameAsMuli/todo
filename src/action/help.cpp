#include <algorithm> // std::sort, ::toupper
#include <iostream>  // std::cout

#include "action/help.hpp"
#include "file/definitions.hpp"

namespace {

void printActionDetails(todo::action::ActionAbstract *const action) {
    auto buffer = action->getName();
    std::transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);

    std::cout << "todo " + buffer + " - " + action->getHelpText() << std::endl;

    buffer = action->usage();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << buffer << std::endl;
    }

    auto aliases = action->getAliases();
    if (aliases.size() > 0) {
        std::cout << std::endl;
        std::cout << "Aliases:" << std::endl;

        bool printComma = false;
        for (auto const &alias : aliases) {
            if (printComma) {
                std::cout << ", ";
            } else {
                printComma = true;
            }
            std::cout << alias;
        }
        std::cout << std::endl;
    }

    buffer = action->description();
    if (!buffer.empty()) {
        std::cout << std::endl;
        std::cout << buffer << std::endl;
    }
}

} // namespace

namespace todo {
namespace action {

Help::Help(util::Input input)
    : ActionAbstract("help", "Display this help text", input, 1) {
    this->addAlias("--help");
}

std::string Help::description() const {
    /* TODO-SAM Write a more detailed description */
    return "Get detailed information on the program or a specific action.";
}

std::string Help::usage() const { return "usage: todo help [<action>]"; }

void Help::addActions(std::vector<ActionAbstract *> &actions) {
    this->m_actions = actions;
    std::sort(this->m_actions.begin(), this->m_actions.end(), actionCompare);
}

void Help::printUsage() const {
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

        /* TODO-SAM Wrap output based on term width - ncurses? */
        std::cout << "TODO Management Utility" << std::endl;
        std::cout << std::endl;

        printUsage();

        std::cout << std::endl;
        std::cout << "If run with no arguments, then any non-archived"
                  << std::endl;
        std::cout << "tasks will be printed. All tasks are stored in:"
                  << std::endl;
        std::cout << file::getTodoDir() << std::endl;
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
        std::cout << "Written by Sam Amis" << std::endl;
    }
}

bool Help::actionCompare(ActionAbstract *a1, ActionAbstract *a2) {
    return a1->getName() < a2->getName();
}

} // namespace action
} // namespace todo
