#include <fstream>  // std::ifstream
#include <iostream> // std::cout

#include "action/view.hpp"
#include "env/todofiles.hpp"

namespace action {

View::View( const util::Input& input):
    ActionAbstract("view", "View outstanding TODOs", input)
{ }

void View::run()
{
    this->urgentTodos();
    this->normalTodos();
    this->lowTodos();
    this->doneTodos();
    this->rejectTodos();
}

void View::archiveTodos() { this->viewTodos(TodoFiles::getArchive()); }
void View::doneTodos() { this->viewTodos(TodoFiles::getDone()); }
void View::lowTodos() { this->viewTodos(TodoFiles::getLow()); }
void View::normalTodos() { this->viewTodos(TodoFiles::getNormal()); }
void View::rejectTodos() { this->viewTodos(TodoFiles::getReject()); }
void View::urgentTodos() { this->viewTodos(TodoFiles::getUrgent()); }

// Private methods
void View::viewTodos(const std::filesystem::path& file)
{
    std::ifstream ifs{file.string()};

    if (ifs.is_open()) {
        // Make sure file isn't empty (rdbuf doesn't like it!)
        if (ifs.peek() != std::ifstream::traits_type::eof()) {
            std::cout << ifs.rdbuf();
        }
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}

} // namespace action
