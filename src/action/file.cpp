#include <regex>  // std::regex
#include <string> // std::string
#include <thread> // std::thread

#include "action/file.hpp"
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
    return "Recursively search for the string '" + current_string +
           "' in specified files. If no input is given, the current directory "
           "will be searched. Otherwise, the input will be treated as the list "
           "of directories to search.\n\n"
           "The default search string is '" +
           default_string + "'. This can be overridden by configuring '" +
           todo_string.to_string() + "'.";
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
    for (const auto &file : files) {
        /* Protect against loading massive files into memory */
        /* Can we detect binary files? */

        auto matches = util::File{file}.search(search_term);
        if (!matches.empty()) {
            std::cout << ANSI_BOLD "[" << file.string() << "]\n" ANSI_RESET;
            for (const auto &line : matches) {
                /* TODO: Strip comment syntax */
                std::cout << util::display::INDENT
                          << util::string::trim_copy(line) << "\n";
            }
        }
    }
}

} // namespace action
} // namespace todo
