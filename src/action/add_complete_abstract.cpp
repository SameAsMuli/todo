#include "action/add_complete_abstract.hpp"
#include "input/option.hpp"

namespace todo {
namespace action {

AddCompleteAbstract::AddCompleteAbstract(const std::string &name,
                                         const std::string &helpText,
                                         const input::Input &input,
                                         task::TaskTypeAbstract *const taskType)
    : AddAbstract(name, helpText, input, taskType) {
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);
}

std::string AddCompleteAbstract::description() const {
    return "Mark any outstanding TODOs as " + this->getTaskType()->getName() +
           " if they match the given input. The TODO will then be considered "
           "as complete.\n\n"
           "By default, the action will match any TODO which is a superset of "
           "the given input, but will only allow a single TODO to be marked "
           "as " +
           this->getTaskType()->getName() +
           "at a time.\n\n"
           "To mark all matched TODOs as " +
           this->getTaskType()->getName() + ", use the " +
           input::Option(input::Option::force).toString() +
           " option. Use the " +
           input::Option(input::Option::exact).toString() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs.";
}

} // namespace action
} // namespace todo
