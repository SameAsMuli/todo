#include <regex>  // std::regex
#include <string> // std::string
#include <thread> // std::thread

#include "action/file.hpp"
#include "task/task.hpp"
#include "task/type.hpp"
#include "util/ansi.hpp"
#include "util/display.hpp"
#include "util/file.hpp"
#include "util/fs.hpp"
#include "util/string.hpp"

namespace todo {
namespace action {

File::File() : ActionAbstract("file", "Find TODOs in files") {
    this->add_related_config(ConfigKey::todo_string);
}

std::string File::description() const {
    ConfigKey todo_string = ConfigKey::todo_string;
    auto default_string = Config::default_value<std::string>(todo_string);
    auto current_string = Config::get_str(todo_string);
    std::stringstream desc;
    desc
        << "Recursively search for the string '" << current_string
        << "' in specified files. If no input is given, the current directory "
           "will be searched. Otherwise, the input will be treated as the list "
           "of directories to search.\n\n"
        << "The search string can be appended with an optional priority in "
           "the file. The syntax for doing so is as follows:\n\n"
        << util::display::INDENT << current_string << "{priority}\n\n"
        << "The following are valid values for 'priority':\n\n";

    for (task::Type const type : task::Type::ALL_TYPES) {
        desc << util::display::INDENT << type.to_string() << "\n";
    }

    desc << "\nThe default search string is '" << default_string
         << "'. This can be overridden by configuring '"
         << todo_string.to_string() << "'.";
    return desc.str();
}

std::string File::usage() const {
    return "usage: todo " + this->get_name() + " [<directory> ...]";
}

void File::run(const input::Input &input) {
    /* Load file list */
    std::deque<std::filesystem::path> files;
    int i = 0;
    while (input.has_action_arg(i)) {
        auto dir = std::filesystem::path{input.get_action_arg(i++)};
        util::fs::get_files_from_dir(dir, files);
    }

    /* If no directories were given, use the current one */
    if (i == 0) {
        util::fs::get_files_from_dir(std::filesystem::current_path(), files);
    }

    /* Search each file for the default string */
    std::string search_term = Config::get<std::string>(ConfigKey::todo_string);
    for (const auto &path : files) {
        /* Protect against loading massive files into memory */
        /* Can we detect binary files? */

        auto file = util::File{path};
        auto matches = file.search(search_term);
        if (!matches.empty()) {
            std::cout << ANSI_BOLD "["
                      << std::filesystem::proximate(path).string()
                      << "]\n" ANSI_RESET;
            for (const auto &line : matches) {
                task::Type task_type = task::Type::normal;

                /* Remove the search term */
                auto comment =
                    line.substr(line.find(search_term) + search_term.length());

                util::string::trim(comment);

                /* Look for a task type specification */
                auto type_str = comment.substr(0, comment.find(" "));
                if (type_str.length() > 2 && type_str[0] == '{' &&
                    type_str[type_str.length() - 1] == '}') {
                    task_type =
                        task::Type{type_str.substr(1, type_str.length() - 2)};
                    if (task_type != task::Type::UNKNOWN) {
                        comment = comment.substr(comment.find(" "));
                    } else {
                        task_type = task::Type::normal;
                    }
                }

                /* Strip any file syntax */
                /* TODO: Strip comment syntax properly */
                if (file.type() == util::File::Type::C ||
                    file.type() == util::File::Type::CPP)
                    comment = comment.substr(0, comment.find("*/"));

                util::string::trim(comment);

                std::cout << task::Task{task_type, comment} << "\n";
            }
        }
    }
}

} // namespace action
} // namespace todo
