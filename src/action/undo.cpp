#include "action/undo.hpp"
#include "file/mutators.hpp"
#include "task/complete_abstract.hpp"

namespace todo {
namespace action {

Undo::Undo(input::Input input)
    : ActionAbstract("undo", "Unmark a TODO as completed", input) {
    this->addAlias("revert");
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);
    this->addValidOption(input::Option::global);
}

std::string Undo::description() const {
    return "Revert any complete TODOs that match the given input back to "
           "outstanding TODOs. TODOs will revert to their original priority "
           "level.\n\n"
           "By default, the action will match any TODO which is a superset of "
           "the given input, but will only allow a single TODO to be undone "
           "at a time.\n\n"
           "To remove all matched TODOs, use the " +
           input::Option(input::Option::force).toString() +
           " option. Use the " +
           input::Option(input::Option::exact).toString() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs.";
}

void Undo::run() { task::CompleteAbstract::undo(this->getInput()); }

} // namespace action
} // namespace todo
