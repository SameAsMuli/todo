#include <exception>  // std::exception
#include <iostream>   // std::cerr
#include <optional>   // std::optional
#include <vector>     // std::vector

#include "action/add.hpp"
#include "action/help.hpp"
#include "action/view.hpp"
#include "env/todofiles.hpp"
#include "util/inputparser.hpp"

int main(int argc, char** argv)
{
    std::optional<TodoFiles> todoFiles;

    try {
        todoFiles.emplace();
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }

    InputParser input{argc, argv};
    std::vector<action::ActionAbstract*> functions;

    action::Help help{};
    functions.push_back(&help);

    action::View view{todoFiles.value(), input};
    functions.push_back(&view);

    functions.push_back(new action::Add{todoFiles.value(), input});

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
