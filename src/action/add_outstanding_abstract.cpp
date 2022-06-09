#include "action/add_outstanding_abstract.hpp"
#include "input/option.hpp"

namespace todo {
namespace action {

AddOutstandingAbstract::AddOutstandingAbstract(
    const std::string &name, const std::string &helpText,
    task::TaskTypeAbstract *const taskType)
    : AddAbstract(name, helpText, taskType) {
    this->addValidOption(input::Option::local);
}

std::string AddOutstandingAbstract::description() const {
    return "Add a new, " + this->getTaskType()->getName() +
           " priority TODO to the specified TODO directory. If the " +
           input::Option(input::Option::local).toString() +
           " option is specified then the current directory will be used, even "
           "if it does not already contain TODO information.\n\n"
           "If a TODO with the same description already exists within the "
           "specified TODO directory then a duplicate will not be created.";
}

} // namespace action
} // namespace todo
