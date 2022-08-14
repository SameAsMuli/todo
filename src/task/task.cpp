#include <sstream> // std::stringstream
#include <string>  // std::getline

#include "task/task.hpp"
#include "util/display.hpp"

namespace {

static const char DELIMITER = ';';

} // namespace

namespace todo {
namespace task {

Task::Task() {}

Task::Task(Type type, std::string &description)
    : m_type(type), m_description(description) {}

void Task::setDescription(const std::string &description) {
    util::string::trim_copy(description);
    m_description = description;
}

void Task::setDescription(const std::string &&description) {
    util::string::trim_copy(description);
    m_description = description;
}

std::ostream &operator<<(std::ostream &stream, const Task &task) {
    stream << util::display::wrap(
        task.getType().formatDescription(task.getDescription()), std::nullopt,
        2);
    return stream;
}

} // namespace task
} // namespace todo
