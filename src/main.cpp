#include <exception> // std::exception
#include <iostream>  // std::cerr
#include <string>    // std::string
#include <utility>   // std::pair
#include <vector>    // std::vector

#include "action/add.hpp"
#include "action/archive.hpp"
#include "action/help.hpp"
#include "action/remove.hpp"
#include "action/undo.hpp"
#include "action/version.hpp"
#include "action/view.hpp"
#include "file/mutators.hpp"
#include "input/input.hpp"
#include "input/option.hpp"
#include "task/type.hpp"
#include "util/display.hpp"

int main(int argc, char **argv) {
    /* Create the data files if they don't already exist */
    try {
        todo::file::initialise(true);
    } catch (const std::exception &e) {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }

    /* Read any input given to the program */
    input::Input input;
    try {
        input = input::Input{argc, argv};
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
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
        actions.push_back(new todo::action::Add{type});
    }

    actions.push_back(new todo::action::Archive{});
    actions.push_back(new todo::action::Remove{});
    actions.push_back(new todo::action::Undo{});
    actions.push_back(new todo::action::Version{});

    /* Pass the list of actions to the help action */
    help.addActions(actions);

    /* If no action is given, then view all tasks. Else run the given action */
    auto inputAction = input.getAction();
    try {
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

            std::cerr << "Unknown action: '" << inputAction << "'" << std::endl;
            std::cout << std::endl;
            std::cout << util::display::programUsage() << std::endl;
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
