#include "action/remove.hpp"
#include "error/empty_argument.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "input/option.hpp"

namespace todo {
namespace action {

Remove::Remove(input::Input input)
    : ActionAbstract("remove", "Remove an outstanding TODO", input,
                     {input::Option::global, input::Option::local}) {}

void Remove::run() {
    /* Form and check the seach string */
    auto searchString = this->getInput().getActionArgString();
    if (searchString.empty()) {
        throw error::EmptyArgument{"remove"};
    }

    file::removeTask(searchString,
                     file::getOutstanding(
                         this->getInput().hasOption(input::Option::global)));
}

} // namespace action
} // namespace todo
