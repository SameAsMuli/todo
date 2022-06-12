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

void Task::setDescription(std::string &description) {
    util::string::trim(description);
    m_description = description;
}

std::istream &operator>>(std::istream &stream, Task &task) {
    std::string description;
    std::string previousType;
    std::string previousTimestamp;
    std::time_t time;
    std::string timestamp;
    std::string type;

    if (std::getline(stream, type, DELIMITER) &&
        std::getline(stream, timestamp, DELIMITER) &&
        std::getline(stream, previousType, DELIMITER) &&
        std::getline(stream, previousTimestamp, DELIMITER) &&
        std::getline(stream, description)) {
        /* Decode the type */
        task.m_type = Type(type);

        /* Decode the time added timestamp */
        std::stringstream ss{timestamp};
        ss >> time;
        if (ss.fail()) {
            stream.setstate(std::ios::failbit);
            return stream;
        }
        task.m_timeAdded = std::chrono::system_clock::from_time_t(time);

        /* Decode the previous type */
        task.m_previousType = Type(previousType);

        /* Decode the previous time added timestamp */
        ss = std::stringstream{previousTimestamp};
        ss >> time;
        if (ss.fail()) {
            stream.setstate(std::ios::failbit);
            return stream;
        }
        task.m_previousTimeAdded = std::chrono::system_clock::from_time_t(time);

        /* Decode the description of the task */
        task.setDescription(description);
    } else {
        /* One operation failed so set the state on the main stream to
         * indicate failure. */
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Task &task) {
    /* Output the task type to the stream */
    stream << task.getType().toString() << DELIMITER;

    /* Output the time added to the stream */
    stream << std::chrono::system_clock::to_time_t(task.getTimeAdded())
           << DELIMITER;

    /* Output the previous task type to the stream */
    stream << task.getPreviousType().toString() << DELIMITER;

    /* Output the previous time added to the stream */
    stream << std::chrono::system_clock::to_time_t(task.getPreviousTimeAdded())
           << DELIMITER;

    /* Output the description */
    stream << task.getDescription();

    return stream;
}

} // namespace task
} // namespace todo
