#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::runtime_error

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace task {

TaskTypeAbstract::TaskTypeAbstract(
    const std::function<std::filesystem::path(bool)> &f_file,
    const std::string &name, const Prefix &prefix)
    : m_f_file(f_file), m_name(name), m_prefix(prefix) {}

std::filesystem::path TaskTypeAbstract::getFile(bool global) const {
    return this->m_f_file(global);
}

void TaskTypeAbstract::view(bool global) {
    std::ifstream ifs{this->getFile(global).string()};

    if (ifs.is_open()) {
        Task task;
        while (ifs >> task) {
            if (this->getPrefix() == task.getPrefix()) {
                std::cout << this->format(task) << std::endl;
            }
        }
    }
}

std::ostream &operator<<(std::ostream &stream,
                         const TaskTypeAbstract *taskType) {
    stream << taskType->getPrefix() << std::endl;
    return stream;
}

} // namespace task
} // namespace todo
