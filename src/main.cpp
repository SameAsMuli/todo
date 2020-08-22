#include <exception>  // std::exception
#include <iostream>   // std::cerr
#include <vector>     // std::vector

#include "action/add.hpp"
#include "action/help.hpp"
#include "action/low.hpp"
#include "action/urgent.hpp"
#include "action/view.hpp"
#include "env/todofiles.hpp"
#include "util/input.hpp"

int main(int argc, char** argv)
{
    try {
        TodoFiles::initialise();
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }

    util::Input input{argc, argv};
    std::vector<action::ActionAbstract*> actions;

    action::Help help{input};
    actions.push_back(&help);

    action::View view{input};
    actions.push_back(&view);

    actions.push_back(new action::Urgent{input, TodoFiles::getUrgent()});
    actions.push_back(new action::Add{input, TodoFiles::getNormal()});
    actions.push_back(new action::Low{input, TodoFiles::getLow()});

    help.addFunctions(actions);

    if (input.isEmpty()) {
        view.run();
    }
    else {
        for (auto const& action:actions) {
            if (input.hasOption(action->getName(), 0)) {
                try {
                    action->perform();
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    return 1;
                }
                return 0;
            }
        }

        std::cerr << "Unknown action: '" << input.getOption(0)
            << "'" << std::endl;
        return 1;
    }

    return 0;
}
