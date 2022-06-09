#include "action/remove.hpp"
#include "error/empty_argument.hpp"
#include "file/definitions.hpp"
#include "file/mutators.hpp"

namespace todo {
namespace action {

Remove::Remove() : ActionAbstract("remove", "Remove an outstanding TODO") {
    this->addValidOption(input::Option::exact);
    this->addValidOption(input::Option::force);
    this->addValidOption(input::Option::global);
}

std::string Remove::description() const {
    return "Remove any outstanding TODOs that match the given input. Complete "
           "TODOs will not be considered for removal.\n\n"
           "By default, the action will match any TODO which is a superset of "
           "the given input, but will only allow a single TODO to be removed "
           "at a time.\n\n"
           "To remove all matched TODOs, use the " +
           input::Option(input::Option::force).toString() +
           " option. Use the " +
           input::Option(input::Option::exact).toString() +
           " option to only match TODOs that have the same description as the "
           "input, and not match against superset TODOs.";
}

void Remove::run(const input::Input &input) {
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
