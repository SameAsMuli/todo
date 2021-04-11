#include "action/archive.hpp"
#include "file/mutators.hpp"
#include "input/option.hpp"
#include "util/string.hpp"

namespace todo {
namespace action {

Archive::Archive(input::Input input)
    : ActionAbstract("archive", "Archive all complete TODOs", input, 1) {
    this->addValidOption(input::Option::global);
}

std::string Archive::description() const {
    return "Move all tasks to an archive file if they were completed more than "
           "the given number of minutes ago. If run with no arguments, then "
           "any completed task is archived.\n\n"
           "Once archived, tasks will no longer appear when the base view "
           "action is called. By default, any task older than 24 hours is "
           "automatically archived.";
}

std::string Archive::usage() const {
    return "usage: todo archive [number of minutes]";
}

void Archive::run() {
    auto input = this->getInput();
    int mins = 0;

    if (input.hasActionArg(0)) {
        mins = util::string::toint(input.getActionArg(0));
    }

    file::archive(mins, input.hasOption(input::Option::global));
}

} // namespace action
} // namespace todo
