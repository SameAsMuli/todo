#include "action/undo.hpp"
#include "task/complete_abstract.hpp"
#include "todo/files.hpp"

namespace action {

Undo::Undo(util::Input input)
    : ActionAbstract("undo", "Unmark a TODO as completed", input) {}

void Undo::run() { task::CompleteAbstract::undo(this->getInput()); }

} // namespace action
