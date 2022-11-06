#include <sstream> // std::stringstream
#include <string>  // std::getline

#include "task/task.hpp"
#include "util/display.hpp"

namespace todo {
namespace task {

Task::Task() {}

Task::Task(Type type, std::string &description)
    : m_type(type), m_description(description) {}

bool Task::is_complete() const { return this->get_type().is_complete(); }

void Task::set_description(const std::string &description) {
    util::string::trim_copy(description);
    m_description = description;
}

void Task::set_description(const std::string &&description) {
    util::string::trim_copy(description);
    m_description = description;
}

std::ostream &operator<<(std::ostream &stream, const Task &task) {
    stream << util::display::wrap(
        task.get_type().format_description(task.get_description()),
        std::nullopt, 2);
    return stream;
}

} // namespace task
} // namespace todo
