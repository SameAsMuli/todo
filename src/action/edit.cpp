#include <stdlib.h>

#include "action/edit.hpp"
#include "error/inspecific_task.hpp"
#include "error/unknown_task.hpp"
#include "file/tasks_data.hpp"
#include "util/env.hpp"

namespace {

static const std::vector<std::string> EDITOR_COMMANDS = {"nvim", "vim", "nano",
                                                         "vi", "emacs"};

} // namespace

namespace todo {
namespace action {

Edit::Edit() : ActionAbstract("edit", "Edit a specific TODO", 0) {
    this->add_valid_option(input::Option::global);
}

std::string Edit::description() const {
    return "Edit a specific TODO through an interactive editor. The inputs to "
           "this action will be used to search TODO descriptions to find a "
           "matching item to alter. Only one TODO can be modified at a time. "
           "Both outstanding and complete TODOs will be considered.";
}

std::string Edit::usage() const {
    return "usage: todo " + this->get_name() + " <task description>";
}

void Edit::run(const input::Input &input) {
    /* Open the tasks file */
    auto tasksData = file::TasksData{file::File::tasks,
                                     input.has_option(input::Option::global)};

    /* Choose the editor to use */
    auto var = std::getenv("EDITOR");
    std::string editor = (var == NULL ? "" : util::string::trim_copy(var));

    if (editor.empty()) {
        for (const auto &command : EDITOR_COMMANDS) {
            if (util::env::command_exists(command)) {
                editor = command;
                break;
            }
        }

        if (editor.empty()) {
            throw std::runtime_error{
                "No editor found. Please set the EDITOR environment variable "
                "to the name of the editor you want to use."};
        }
    } else if (!util::env::command_exists(editor)) {
        throw std::runtime_error{
            "The editor specified in the EDITOR environment variable "
            "does not exist."};
    }

    /* Backup the tasks file */
    tasksData.read();
    auto backup = tasksData;

    /* Construct and run the edit command */
    auto command = editor + " " + tasksData.get_file().string();
    std::system(command.c_str());

    /* Check that the tasks file is still valid */
    try {
        tasksData.read();
    } catch (const std::exception &e) {
        /* Restore the backup */
        backup.write();
        throw std::runtime_error{
            std::string{"reverting changes, error found in tasks file: "} +
            e.what()};
    }
}

} // namespace action
} // namespace todo
