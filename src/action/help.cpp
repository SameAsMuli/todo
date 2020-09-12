#include <algorithm> // std::sort
#include <iostream>  // std::cout
#include <string>    // std::string

#include "action/help.hpp"

namespace action {

Help::Help(util::Input input)
    : ActionAbstract("help", "Display this help text", input, 1) {}

void Help::addFunctions(std::vector<ActionAbstract *> &functions) {
    this->m_functions = functions;
    std::sort(this->m_functions.begin(), this->m_functions.end(), todoFuncComp);
}

void Help::run() {
    std::string::size_type maxNameLen = 0;
    std::vector<ActionAbstract *>::size_type minSeparatorLen = 3;

    for (auto const &func : this->m_functions) {
        if (maxNameLen < func->getName().size()) {
            maxNameLen = func->getName().size();
        }
    }

    /* TODO-SAM Wrap output based on term width - ncurses? */
    std::cout << "TODO Management Utility" << std::endl;
    std::cout << std::endl;
    std::cout << "If run with no arguments will print all TODOs found"
              << std::endl;
    std::cout << "in the todo file." << std::endl;
    std::cout << std::endl;
    std::cout << "Value of the todo file defaults to '~/.config/todo'"
              << std::endl;
    std::cout << "but can be overridden using $TODO_FILE." << std::endl;
    std::cout << std::endl;
    std::cout << "List of commands:" << std::endl;

    for (auto const &func : this->m_functions) {
        std::cout << "  " + func->getName() + " " +
                         std::string(minSeparatorLen +
                                         (maxNameLen - func->getName().size()),
                                     '.') +
                         " " + func->getHelpText()
                  << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Written by Sam Amis" << std::endl;
}

bool Help::todoFuncComp(ActionAbstract *tf1, ActionAbstract *tf2) {
    return tf1->getName() < tf2->getName();
}

} // namespace action
