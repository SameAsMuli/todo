#include <algorithm> // std::sort
#include <iostream>  // std::cout

#include "HelpFunction.hpp"

bool todoFuncComp(TodoFunction* tf1, TodoFunction* tf2 )
{
    return tf1->getName() < tf2->getName();
}

HelpFunction::HelpFunction():TodoFunction("help", "Display this help text")
{
    this->addFunction(this);
}

void HelpFunction::addFunction(TodoFunction* func)
{
    this->funcs.push_back(func);
}

void HelpFunction::run()
{
    std::string::size_type maxNameLen = 0;
    std::vector<TodoFunction*>::size_type minSeparatorLen = 3;


    std::sort(this->funcs.begin(), this->funcs.end(), todoFuncComp);

    for (std::vector<TodoFunction*>::size_type i = 0; i < this->funcs.size(); i++) {
        if (maxNameLen < this->funcs.at(i)->getName().size()) {
            maxNameLen = this->funcs.at(i)->getName().size();
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

    for (std::vector<TodoFunction*>::size_type i = 0; i < this->funcs.size(); i++) {
        TodoFunction* todoFunc = this->funcs.at(i);
        std::cout << "  " + todoFunc->getName() + " " +
            std::string(minSeparatorLen +
                    (maxNameLen - todoFunc->getName().size()), '.') +
            " " + todoFunc->getHelpText() << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Written by Sam Amis" << std::endl;
}
