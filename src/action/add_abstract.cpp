#include <fstream>  // std::ofstream

#include "action/add_abstract.hpp"

namespace action {

AddAbstract::AddAbstract(
        const std::string& name,
        const std::string& helpText,
        const util::Input& input,
        task::TaskTypeAbstract *const taskType):
    ActionAbstract(name, helpText, input),
    m_taskType(taskType)
{ }

void AddAbstract::run()
{
    this->m_taskType->add(this->getInput());
}

} // namespace action
