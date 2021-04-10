#include <fstream> // std::ofstream

#include "action/add_abstract.hpp"
#include "input/option.hpp"

namespace {

std::unordered_set<input::Option>
includeGlobalOption(const std::unordered_set<input::Option> &validOptions) {
    std::unordered_set<input::Option> set{input::Option::global};
    set.insert(validOptions.begin(), validOptions.end());
    return set;
}

} // namespace

namespace todo {
namespace action {

AddAbstract::AddAbstract(const std::string &name, const std::string &helpText,
                         const input::Input &input,
                         const std::unordered_set<input::Option> &validOptions,
                         task::TaskTypeAbstract *const taskType)
    : ActionAbstract(name, helpText, input, includeGlobalOption(validOptions)),
      m_taskType(taskType) {}

void AddAbstract::run() { this->m_taskType->add(this->getInput()); }

} // namespace action
} // namespace todo
