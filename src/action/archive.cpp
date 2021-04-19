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
    return "Move all TODOs to an archive file if they were completed more than "
           "the given number of minutes ago. If run with no arguments, then "
           "any completed TODO is archived.\n\n"
           "Once archived, TODOs will no longer appear when the view action is "
           "called. By default, any TODO older than 24 hours is automatically "
           "archived.";
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
