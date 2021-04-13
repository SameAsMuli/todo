#include "action/remove.hpp"
#include "error/empty_argument.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "input/option.hpp"

namespace todo {
namespace action {

Remove::Remove(input::Input input)
    : ActionAbstract("remove", "Remove an outstanding TODO", input) {
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);
    this->addValidOption(input::Option::global);
}

void Remove::run() {
    auto input = this->getInput();

    /* Form and check the seach string */
    auto searchString = input.getActionArgString();
    if (searchString.empty()) {
        throw error::EmptyArgument{"remove"};
    }

    file::removeTasks(
        searchString,
        file::getOutstanding(input.hasOption(input::Option::global)),
        input.hasOption(input::Option::force),
        input.hasOption(input::Option::exact));
}

} // namespace action
} // namespace todo
