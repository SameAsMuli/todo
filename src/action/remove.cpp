#include "action/remove.hpp"
#include "todo/empty_argument.hpp"
#include "todo/files.hpp"

namespace action {

Remove::Remove(util::Input input)
    : ActionAbstract("remove", "Remove an outstanding TODO", input) {}

void Remove::run() {
    /* Form and check the seach string */
    auto searchString =
        this->getInput().toString(util::Input::PARAM_START_INDEX);
    if (searchString.empty()) {
        throw todo::EmptyArgument{"remove"};
    }

    todo::files::removeTask(searchString, todo::files::getOutstanding());
}

} // namespace action
