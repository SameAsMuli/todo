#include <fstream>  // std::ifstream
#include <iostream> // std::cout

#include "ViewFunction.hpp"

ViewFunction::ViewFunction(
        const TodoFiles& todoFiles,
        const InputParser& input):
    TodoFunctionAbstract("view", "View outstanding TODOs"),
    m_input(input),
    m_todoFiles(todoFiles)
{ }

void ViewFunction::run()
{
    this->urgentTodos();
    this->normalTodos();
    this->lowTodos();
    this->doneTodos();
}

void ViewFunction::archiveTodos() {}
void ViewFunction::doneTodos() {}
void ViewFunction::lowTodos() {}
void ViewFunction::normalTodos()
{
    std::ifstream ifs{this->m_todoFiles.getNormal().string()};

    if (ifs.is_open()) {
        std::cout << ifs.rdbuf();
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}
void ViewFunction::rejectTodos() {}
void ViewFunction::urgentTodos() {}
