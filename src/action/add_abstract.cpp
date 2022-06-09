#include <fstream> // std::ofstream

#include "action/add_abstract.hpp"
#include "input/option.hpp"

namespace todo {
namespace action {

AddAbstract::AddAbstract(const std::string &name, const std::string &helpText,
                         task::TaskTypeAbstract *const taskType)
    : ActionAbstract(name, helpText), m_taskType(taskType) {
    this->addValidOption(input::Option::global);
}

void AddAbstract::run(const input::Input &input) {
    this->m_taskType->add(input);
}

std::string AddAbstract::usage() const {
    return "usage: todo " + this->getName() + " [<task description>]";
}

} // namespace action
} // namespace todo
