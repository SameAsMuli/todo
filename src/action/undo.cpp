#include "action/undo.hpp"
#include "file/mutators.hpp"
#include "input/option_type.hpp"
#include "task/complete_abstract.hpp"

namespace todo {
namespace action {

Undo::Undo(input::Input input)
    : ActionAbstract("undo", "Unmark a TODO as completed", input,
                     {input::OptionType::global, input::OptionType::local}) {}

void Undo::run() { task::CompleteAbstract::undo(this->getInput()); }

} // namespace action
} // namespace todo
