#include <fstream>  // std::ifstream
#include <iostream> // std::cout

#include "action/view.hpp"

namespace action {

View::View(
        const TodoFiles& todoFiles,
        const util::InputParser& input):
    ActionAbstract("view", "View outstanding TODOs"),
    m_input(input),
    m_todoFiles(todoFiles)
{ }

void View::run()
{
    this->urgentTodos();
    this->normalTodos();
    this->lowTodos();
    this->doneTodos();
}

void View::archiveTodos() {}
void View::doneTodos() {}
void View::lowTodos() {}
void View::normalTodos()
{
    std::ifstream ifs{this->m_todoFiles.getNormal().string()};

    if (ifs.is_open()) {
        std::cout << ifs.rdbuf();
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}
void View::rejectTodos() {}
void View::urgentTodos() {}

} // namespace action
