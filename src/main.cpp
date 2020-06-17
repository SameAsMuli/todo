#include <cstdlib>    // std::getenv
#include <exception>  // std::exception
#include <filesystem> // std::filesystem
#include <fstream>    // std::ofstream
#include <iostream>   // std::cerr
#include <string>     // std::string
#include <vector>     // std::vector

#include "AddFunction.hpp"
#include "HelpFunction.hpp"
#include "InputParser.hpp"
#include "ViewFunction.hpp"

namespace fs = std::filesystem;

void initialise(fs::path& todoFile) {
    // Find the specified path to the todo file
    if (std::getenv("TODO_FILE")) {
        todoFile.assign(std::getenv("TODO_FILE"));

    } else if (std::getenv("HOME")) {
        std::string homeDir = std::getenv("HOME");
        todoFile.assign(homeDir+"/.config/todo/todo_file");

    } else {
        throw std::runtime_error("Neither $TODO_FILE nor $HOME are defined");
    }

    // Create parent directory if it doesn't already exist
    fs::create_directories(todoFile.parent_path());

    // Create todoFile if it doesn't already exist
    if (!fs::exists(todoFile)) {
        std::ofstream(todoFile.string()); // create file
    }
}

int main(int argc, char** argv)
{
    fs::path todoFile;

    try {
        initialise(todoFile);
    } catch (const std::exception& e) {
        std::cerr << "Failed to initialise: " << e.what() << std::endl;
        return 1;
    }

    InputParser input{argc, argv};
    std::vector<TodoFunctionAbstract*> functions;

    HelpFunction help{};
    functions.push_back(&help);

    ViewFunction view{todoFile, input};
    functions.push_back(&view);

    functions.push_back(new AddFunction{todoFile, input});

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
