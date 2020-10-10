#include <fstream>   // std::ifstream
#include <iostream>  // std::cout
#include <stdexcept> // std::runtime_error

#include "task/task.hpp"
#include "task/task_type_abstract.hpp"

namespace todo {
namespace task {

TaskTypeAbstract::TaskTypeAbstract(const std::filesystem::path &file,
                                   Prefix prefix)
    : m_file(file), m_prefix(prefix) {}

void TaskTypeAbstract::view() {
    std::ifstream ifs{this->getFile().string()};

    if (ifs.is_open()) {
        Task task;
        while (ifs >> task) {
            if (this->getPrefix() == task.getPrefix()) {
                std::cout << this->format(task) << std::endl;
            }
        }
    } else {
        throw std::runtime_error{"Unable to open TODO file"};
    }
}

std::ostream &operator<<(std::ostream &stream,
                         const TaskTypeAbstract *taskType) {
    stream << taskType->getPrefix() << std::endl;
    return stream;
}

} // namespace task
} // namespace todo
