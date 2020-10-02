#include "action/remove.hpp"
#include "todo/files.hpp"

namespace action {

Remove::Remove(util::Input input)
    : ActionAbstract("remove", "Remove an outstanding TODO", input) {}

void Remove::run() {
    todo::files::removeTask(
        this->getInput().toString(util::Input::PARAM_START_INDEX),
        todo::files::getOutstanding());
}

} // namespace action
