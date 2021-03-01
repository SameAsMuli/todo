#include "action/archive.hpp"
#include "file/mutators.hpp"

namespace todo {
namespace action {

Archive::Archive(util::Input input)
    : ActionAbstract("archive", "Archive all complete TODOs", input, 0) {}

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
    // TODO-SAM Allow number of minutes to be changed
    file::archive(0);
}

} // namespace action
} // namespace todo
