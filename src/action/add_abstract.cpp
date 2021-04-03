#include <fstream> // std::ofstream

#include "action/add_abstract.hpp"
#include "input/option.hpp"

namespace todo {
namespace action {

AddAbstract::AddAbstract(const std::string &name, const std::string &helpText,
                         const input::Input &input,
                         task::TaskTypeAbstract *const taskType)
    : ActionAbstract(name, helpText, input,
                     {input::Option::global, input::Option::local}),
      m_taskType(taskType) {}

void AddAbstract::run() { this->m_taskType->add(this->getInput()); }

} // namespace action
} // namespace todo
