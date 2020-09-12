#include <sstream> // std::stringstream
#include <string>  // std::getline

#include "task/task.hpp"

namespace task {

Task::Task()
{ }

std::istream& operator>>(std::istream& stream, Task& task)
{
    std::string description;
    std::string line;
    std::string prefix;

    if (std::getline(stream, line)) {
        std::stringstream iss(line);
        if (std::getline(iss, prefix, ' ') &&
            std::getline(iss, description)) {
            // TODO-SAM Should we verify prefix has length 1?
            task.m_prefix = prefix[0];
            task.m_description = description;
        } else {
            // One operation failed so set the state on
            // the main stream to indicate failure.
            stream.setstate(std::ios::failbit);
        }
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream, Task& task)
{
    stream << task.getPrefix() << " " << task.getDescription() << std::endl;
    return stream;
}

} // namespace task
