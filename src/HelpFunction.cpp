#include <algorithm> // std::sort
#include <iostream>  // std::cout

#include "HelpFunction.hpp"

bool todoFuncComp(TodoFunction* tf1, TodoFunction* tf2 )
{
    return tf1->getName() < tf2->getName();
}

HelpFunction::HelpFunction():TodoFunction("help", "Display this help text") { }

void HelpFunction::addFunctions(std::vector<TodoFunction*>& functions)
{
    this->funcs = functions;
    std::sort(this->funcs.begin(), this->funcs.end(), todoFuncComp);
}

void HelpFunction::run()
{
    std::string::size_type maxNameLen = 0;
    std::vector<TodoFunction*>::size_type minSeparatorLen = 3;

    for (auto const& func:this->funcs) {
        if (maxNameLen < func->getName().size()) {
            maxNameLen = func->getName().size();
        }
    }

    std::cout << "TODO Management Utility" << std::endl;
    std::cout << std::endl;
    std::cout << "If run with no arguments will print all TODOs found" << std::endl;
    std::cout << "in the todo file." << std::endl;
    std::cout << std::endl;
    std::cout << "Value of the todo file defaults to '~/.config/todo'" << std::endl;
    std::cout << "but can be overriden using $TODO_FILE." << std::endl;
    std::cout << std::endl;
    std::cout << "List of commands:" << std::endl;

    for (auto const& func:this->funcs) {
        std::cout << "  " + func->getName() + " " +
            std::string(minSeparatorLen +
                    (maxNameLen - func->getName().size()), '.') +
            " " + func->getHelpText() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Written by Sam Amis" << std::endl;
}
