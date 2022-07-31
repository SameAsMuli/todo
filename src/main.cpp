#include <exception> // std::exception
#include <iostream>  // std::cerr
#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

#include "action/add.hpp"
#include "action/archive.hpp"
#include "action/complete.hpp"
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

static const std::string ERR_PREFIX = "todo: ";

int main(int argc, char **argv) {
    /* Sanity check the environment and perform any archiving that's needed */
    try {
        if (util::fs::HomeDir().empty()) {
            throw std::runtime_error{"unable to find HOME directory"};
        }

        /* Archive any tasks completed more than a day ago */
        todo::file::archiveTasks(1440, true);
        todo::file::archiveTasks(1440, false);
    } catch (const std::exception &e) {
        std::cerr << ERR_PREFIX << e.what() << std::endl;
        return 1;
    }

    /* Read any input given to the program */
    input::Input input;
    try {
        input = input::Input{argc, argv};
    } catch (const std::exception &e) {
        std::cerr << ERR_PREFIX << e.what() << std::endl;
        return 1;
    }

    /* Create a list of actions */
    std::vector<todo::action::ActionAbstract *> actions;

    todo::action::Help help{};
    actions.push_back(&help);

    todo::action::View view{};
    actions.push_back(&view);

    /* Create an action to add each type of task */
    for (auto const type : todo::task::Type::ALL_TYPES) {
        if (todo::task::Type{type}.isComplete()) {
            actions.push_back(new todo::action::Complete{type});
        } else {
            actions.push_back(new todo::action::Add{type});
        }
    }

    actions.push_back(new todo::action::Archive{});
    actions.push_back(new todo::action::Remove{});
    actions.push_back(new todo::action::Search{});
    actions.push_back(new todo::action::Undo{});
    actions.push_back(new todo::action::Version{});

    /* Pass the list of actions to the help action */
    help.addActions(actions);

    auto inputAction = input.getAction();
    try {
        /* If no action is given, view all tasks - else run the given action */
        if (inputAction.empty()) {
            if (input.hasOption(input::Option::help)) {
                std::vector<std::pair<std::string, std::string>> actionList;
                for (auto const &action : actions) {
                    actionList.push_back(
                        {action->getName(), action->getHelpText()});
                }

                std::cout << util::display::programOverview(actionList)
                          << std::endl;
            } else {
                view.perform(input);
            }
        } else {
            for (auto const &action : actions) {
                if (action->isKnownAs(inputAction)) {
                    action->perform(input);
                    return 0;
                }
            }

            /* The given action isn't known, display usage and corrections */
            std::vector<std::string> actionNames;
            for (auto const &action : actions) {
                actionNames.push_back(action->getName());
            }

            auto corrections =
                util::string::corrections(inputAction, actionNames);

            std::cerr << ERR_PREFIX << "unknown action '" << inputAction << "'"
                      << std::endl;

            if (corrections.size() > 0) {
                std::cout << "(did you mean ";

                if (corrections.size() > 1) {
                    std::cout << "one of ";
                }

                int i = 0;
                for (auto const &str : corrections) {
                    if (i++ > 0) {
                        std::cout << ", ";
                    }
                    std::cout << str;
                }

                std::cout << "?)" << std::endl;
            }

            std::cout << std::endl;
            std::cout << util::display::programUsage() << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << ERR_PREFIX << e.what() << std::endl;
        return 1;
    }

    return 0;
}
