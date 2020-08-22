#include <fstream>  // std::ifstream
#include <iostream> // std::cout

#include "action/unknown_argument.hpp"
#include "action/view.hpp"
#include "env/todofiles.hpp"

namespace action {

View::View( const util::Input& input):
    ActionAbstract("view", "View outstanding TODOs", input, 1)
{ }

void View::run()
{
    unsigned int index = 1;

    if (!this->getInput().hasOption(index)) {
        this->urgentTodos();
        this->normalTodos();
        this->lowTodos();
        this->doneTodos();
        this->rejectTodos();
        return;
    }

    auto option = this->getInput().getOption(index);

    if (option == "urgent") { this->urgentTodos(); }
    else if (option == "normal") { this->normalTodos(); }
    else if (option == "low") { this->lowTodos(); }
    else if (option == "done") { this->doneTodos(); }
    else if (option == "reject") { this->rejectTodos(); }
    else if (option == "archive") { this->archiveTodos(); }
    else { throw action::UnknownArgument(option); }
}

void View::archiveTodos() const { this->viewTodos(TodoFiles::getArchive()); }
void View::doneTodos() const { this->viewTodos(TodoFiles::getDone()); }
void View::lowTodos() const { this->viewTodos(TodoFiles::getLow()); }
void View::normalTodos() const { this->viewTodos(TodoFiles::getNormal()); }
void View::rejectTodos() const { this->viewTodos(TodoFiles::getReject()); }
void View::urgentTodos() const { this->viewTodos(TodoFiles::getUrgent()); }

// Private methods
void View::viewTodos(const std::filesystem::path& file) const
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
