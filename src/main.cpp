#include <exception>  // std::exception
#include <iostream>   // std::cerr
#include <optional>   // std::optional
#include <vector>     // std::vector

#include "AddFunction.hpp"
#include "HelpFunction.hpp"
#include "InputParser.hpp"
#include "TodoFiles.hpp"
#include "ViewFunction.hpp"

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
    std::vector<TodoFunctionAbstract*> functions;

    HelpFunction help{};
    functions.push_back(&help);

    ViewFunction view{todoFiles.value(), input};
    functions.push_back(&view);

    functions.push_back(new AddFunction{todoFiles.value(), input});

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
