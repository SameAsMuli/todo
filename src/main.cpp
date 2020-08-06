#include <exception>  // std::exception
#include <iomanip>    // std::quoted
#include <iostream>   // std::cerr
#include <vector>     // std::vector

#include "action/add.hpp"
#include "action/help.hpp"
#include "action/low.hpp"
#include "action/urgent.hpp"
#include "action/view.hpp"
#include "env/todofiles.hpp"
#include "util/inputparser.hpp"

int main(int argc, char** argv)
{
    try {
        TodoFiles::initialise();
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }

    util::InputParser input{argc, argv};
    std::vector<action::ActionAbstract*> functions;

    action::Help help{};
    functions.push_back(&help);

    action::View view{input};
    functions.push_back(&view);

    functions.push_back(new action::Urgent{input, TodoFiles::getUrgent()});
    functions.push_back(new action::Add{input, TodoFiles::getNormal()});
    functions.push_back(new action::Low{input, TodoFiles::getLow()});

    help.addFunctions(functions);

    if (input.isEmpty()) {
        view.run();
    }
    else {
        for (auto const& func:functions) {
            if (input.hasOption(func->getName(), 0)) {
                try {
                    func->run();
                } catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    return 1;
                }
                return 0;
            }
        }

        std::cout << "Unknown option: " <<
            std::quoted(input.getOption(0),'\'') << std::endl;

        return 1;
    }

    return 0;
}
