#include <sstream> // std::stringstream
#include <string>  // std::getline

#include "task/task.hpp"
#include "util/string.hpp"

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
    stream << task.getType().formatDescription(task.getDescription());
    return stream;
}

} // namespace task
} // namespace todo
