#include "action/archive.hpp"
#include "error/incompatible_options.hpp"
#include "file/mutators.hpp"
#include "input/option.hpp"
#include "util/string.hpp"

namespace todo {
namespace action {

Archive::Archive()
    : ActionAbstract("archive", "Archive all complete TODOs", 1) {
    this->add_valid_option(input::Option::all);
    this->add_valid_option(input::Option::global);
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
    return "usage: todo " + this->get_name() + " [<number of minutes>]";
}

void Archive::run(const input::Input &input) {
    /* Sense check the options */
    bool all = input.hasOption(input::Option::all);
    bool global = input.hasOption(input::Option::global);

    if (all && global) {
        throw error::IncompatibleOptions(input::Option::all,
                                         input::Option::global);
    }

    /* Get the number of minutes in the past to archive from */
    int mins = 0;

    if (input.has_action_arg(0)) {
        mins = util::string::toint(input.get_actionArg(0));
    }

    if (all) {
        file::archive_tasks(mins, true);
        if (file::get_todo_dir(false) != file::get_todo_dir(true)) {
            file::archive_tasks(mins, false);
        }
    } else {
        file::archive_tasks(mins, global);
    }
}

} // namespace action
} // namespace todo
