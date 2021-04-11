#include "action/undo.hpp"
#include "file/mutators.hpp"
#include "input/option.hpp"
#include "task/complete_abstract.hpp"

namespace todo {
namespace action {

Undo::Undo(input::Input input)
    : ActionAbstract("undo", "Unmark a TODO as completed", input) {
    this->addValidOption(input::Option::global);
    this->addValidOption(input::Option::local);
}

void Undo::run() { task::CompleteAbstract::undo(this->getInput()); }

} // namespace action
} // namespace todo
