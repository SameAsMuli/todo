#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::runtime_error

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace task {

TaskTypeAbstract::TaskTypeAbstract(
    const std::function<std::filesystem::path(bool)> &f_file,
    const std::string &name, const Type &type)
    : m_f_file(f_file), m_name(name), m_type(type) {}

std::filesystem::path TaskTypeAbstract::getFile(bool global) const {
    return this->m_f_file(global);
}

void TaskTypeAbstract::view(bool global) {
    std::ifstream ifs{this->getFile(global).string()};

    if (ifs.is_open()) {
        Task task;
        while (ifs >> task) {
            if (this->getType() == task.getType()) {
                std::cout << this->format(task) << std::endl;
            }
        }
    }
}

std::ostream &operator<<(std::ostream &stream,
                         const TaskTypeAbstract *taskType) {
    stream << taskType->getType() << std::endl;
    return stream;
}

std::string TaskTypeAbstract::format(const Task &task) {
    return this->getType().formatDescription(task.getDescription());
}

} // namespace task
} // namespace todo
