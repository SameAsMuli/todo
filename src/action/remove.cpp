#include "action/remove.hpp"
#include "error/empty_argument.hpp"
#include "file/mutators.hpp"

namespace todo {
namespace action {

Remove::Remove(util::Input input)
    : ActionAbstract("remove", "Remove an outstanding TODO", input) {}

void Remove::run() {
    /* Form and check the seach string */
    auto searchString =
        this->getInput().toString(util::Input::PARAM_START_INDEX);
    if (searchString.empty()) {
        throw error::EmptyArgument{"remove"};
    }

    file::removeTask(searchString, file::getOutstanding());
}

} // namespace action
} // namespace todo
