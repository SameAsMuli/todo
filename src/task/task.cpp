#include <sstream> // std::stringstream
#include <string>  // std::getline

#include "task/task.hpp"

namespace task {

Task::Task() {}

Task::Task(Prefix prefix, std::string &description)
    : m_prefix(prefix), m_description(description) {}

std::istream &operator>>(std::istream &stream, Task &task) {
    std::string description;
    Metadata metadata;
    std::string prefix;

    /* Decode the metadata for the task */
    stream >> metadata;
    if (stream.fail()) {
        return stream;
    }

    task.m_metadata = metadata;

    /* Decode the description of the task */
    if (std::getline(stream, prefix, ' ') &&
        std::getline(stream, description)) {
        task.m_prefix.setCharacter(prefix[0]);
        task.m_description = description;
    } else {
        /* One operation failed so set the state on the main stream to
         * indicate failure. */
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, Task task) {
    stream << task.getMetadata() << task.getPrefix() << " " << task.getDescription();
    return stream;
}

} // namespace task
