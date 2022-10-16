#include <exception> // std::exception
#include <iostream>  // std::cerr
#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

#include "action/add.hpp"
#include "action/archive.hpp"
#include "action/complete.hpp"
#include "action/edit.hpp"
#include "action/help.hpp"
#include "action/remove.hpp"
#include "action/search.hpp"
#include "action/undo.hpp"
#include "action/version.hpp"
#include "action/view.hpp"
#include "file/mutators.hpp"
#include "input/input.hpp"
#include "input/option.hpp"
#include "task/type.hpp"
#include "util/display.hpp"
#include "util/fs.hpp"
#include "util/string.hpp"

static void print_err(const std::string &msg) {
    std::cerr << "todo: " << msg << std::endl;
}

int main(int argc, char **argv) {
    /* Sanity check the environment and perform any archiving that's needed */
    try {
        if (util::fs::home_dir().empty()) {
            throw std::runtime_error{"unable to find HOME directory"};
        }

        /* Archive any tasks completed more than a day ago */
        todo::file::archive_tasks(1440, true);
        todo::file::archive_tasks(1440, false);
    } catch (const std::exception &e) {
        print_err(e.what());
        return 1;
    }

    /* Read any input given to the program */
    input::Input input;
    try {
        input = input::Input{argc, argv};
    } catch (const std::exception &e) {
        print_err(e.what());
        return 1;
    }

    /* Create a list of actions */
    std::vector<todo::action::ActionAbstract *> actions;

    todo::action::Help help{};
    actions.push_back(&help);

    todo::action::View view{};
    actions.push_back(&view);

    /* Create an action to add each type of task */
    for (const auto type : todo::task::Type::ALL_TYPES) {
        if (todo::task::Type{type}.is_complete()) {
            actions.push_back(new todo::action::Complete{type});
        } else {
            actions.push_back(new todo::action::Add{type});
        }
    }

    actions.push_back(new todo::action::Archive{});
    actions.push_back(new todo::action::Edit{});
    actions.push_back(new todo::action::Remove{});
    actions.push_back(new todo::action::Search{});
    actions.push_back(new todo::action::Undo{});
    actions.push_back(new todo::action::Version{});

    /* Pass the list of actions to the help action */
    help.add_actions(actions);

    auto inputAction = input.get_action();
    try {
        /* If no action is given, view all tasks - else run the given action */
        if (inputAction.empty()) {
            if (input.has_option(input::Option::help)) {
                std::vector<std::pair<std::string, std::string>> actionList;
                for (const auto &action : actions) {
                    actionList.push_back(
                        {action->get_name(), action->get_help_text()});
                }

                std::cout << util::display::program_overview(actionList)
                          << std::endl;
            } else {
                view.perform(input);
            }
        } else {
            for (const auto &action : actions) {
                if (action->is_known_as(inputAction)) {
                    action->perform(input);
                    return 0;
                }
            }

            /* The given action isn't known, display usage and corrections */
            std::vector<std::string> actionNames;
            for (const auto &action : actions) {
                actionNames.push_back(action->get_name());
            }

            auto corrections =
                util::string::corrections(inputAction, actionNames);

            print_err("unknown action '" + inputAction + "'");

            if (corrections.size() > 0) {
                std::cout << "(did you mean ";

                if (corrections.size() > 1) {
                    std::cout << "one of ";
                }

                int i = 0;
                for (const auto &str : corrections) {
                    if (i++ > 0) {
                        std::cout << ", ";
                    }
                    std::cout << str;
                }

                std::cout << "?)" << std::endl;
            }

            std::cout << std::endl;
            std::cout << util::display::program_usage() << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        print_err(e.what());
        return 1;
    }

    return 0;
}
