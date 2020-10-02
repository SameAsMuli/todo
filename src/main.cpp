#include <exception> // std::exception
#include <iostream>  // std::cerr
#include <vector>    // std::vector

#include "action/add.hpp"
#include "action/done.hpp"
#include "action/help.hpp"
#include "action/low.hpp"
#include "action/reject.hpp"
#include "action/remove.hpp"
#include "action/undo.hpp"
#include "action/urgent.hpp"
#include "action/view.hpp"
#include "todo/files.hpp"
#include "util/input.hpp"

int main(int argc, char **argv) {
    /* Create the data files if they don't already exist */
    try {
        todo::files::initialise();
    } catch (const std::exception &e) {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }

    /* Read any input given to the program */
    util::Input input{argc, argv};

    /* Create a list of actions */
    std::vector<action::ActionAbstract *> actions;

    action::Help help{input};
    actions.push_back(&help);

    action::View view{input};
    actions.push_back(&view);

    actions.push_back(new action::Add{input});
    actions.push_back(new action::Done{input});
    actions.push_back(new action::Low{input});
    actions.push_back(new action::Reject{input});
    actions.push_back(new action::Remove{input});
    actions.push_back(new action::Undo{input});
    actions.push_back(new action::Urgent{input});

    /* Pass the list of actions to the help action */
    help.addFunctions(actions);

    /* If no input is given, then view all tasks. Else run the given action */
    if (input.isEmpty()) {
        view.run();
    } else {
        for (auto const &action : actions) {
            if (input.hasOption(action->getName(), util::Input::ACTION_INDEX)) {
                try {
                    action->perform();
                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                    return 1;
                }
                return 0;
            }
        }

        std::cerr << "Unknown action: '"
                  << input.getOption(util::Input::ACTION_INDEX) << "'"
                  << std::endl;
        return 1;
    }

    return 0;
}
