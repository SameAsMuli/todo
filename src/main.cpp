#include <algorithm> // std::find
#include <exception> // std::exception
#include <iostream>  // std::cerr
#include <vector>    // std::vector

#include "action/add.hpp"
#include "action/archive.hpp"
#include "action/done.hpp"
#include "action/help.hpp"
#include "action/high.hpp"
#include "action/low.hpp"
#include "action/reject.hpp"
#include "action/remove.hpp"
#include "action/undo.hpp"
#include "action/urgent.hpp"
#include "action/view.hpp"
#include "file/mutators.hpp"
#include "util/input.hpp"

int main(int argc, char **argv) {
    /* Create the data files if they don't already exist */
    try {
        todo::file::initialise();
    } catch (const std::exception &e) {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }

    /* Read any input given to the program */
    util::Input input{argc, argv};

    /* Create a list of actions */
    std::vector<todo::action::ActionAbstract *> actions;

    todo::action::Help help{input};
    actions.push_back(&help);

    todo::action::View view{input};
    actions.push_back(&view);

    actions.push_back(new todo::action::Add{input});
    actions.push_back(new todo::action::Archive{input});
    actions.push_back(new todo::action::Done{input});
    actions.push_back(new todo::action::High{input});
    actions.push_back(new todo::action::Low{input});
    actions.push_back(new todo::action::Reject{input});
    actions.push_back(new todo::action::Remove{input});
    actions.push_back(new todo::action::Undo{input});
    actions.push_back(new todo::action::Urgent{input});

    /* Pass the list of actions to the help action */
    help.addActions(actions);

    /* If no input is given, then view all tasks. Else run the given action */
    if (input.isEmpty()) {
        view.run();
    } else {
        auto inputAction = input.getOption(util::Input::ACTION_INDEX);
        if (!inputAction.empty()) {
            for (auto const &action : actions) {
                if (action->isKnownAs(inputAction)) {
                    try {
                        action->perform();
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                        return 1;
                    }
                    return 0;
                }
            }
        }

        std::cerr << "Unknown action: '"
                  << input.getOption(util::Input::ACTION_INDEX) << "'"
                  << std::endl;
        std::cout << std::endl;
        help.printGeneralUsage();
        return 1;
    }

    return 0;
}
