#include <cstdlib>    // std::getenv
#include <exception>  // std::exception
#include <filesystem> // std::filesystem
#include <iostream>   // std::cout
#include <string>     // std::string
#include <vector>     // std::vector

#include "AddFunction.hpp"
#include "HelpFunction.hpp"
#include "InputParser.hpp"

namespace fs = std::filesystem;

/* void initialise(const fs::path todoFile) { */
/*     // Create parent directory if it doesn't already exist */
/*     fs::create_directories(todoFile.parent_path()); */
/*     // Create todoFile if it doesn't already exist */
/*     if (fs::exists(todoFile)) { */
/*         if (fs::status(todoFile).type() != fs::file_type::regular || */
/*                 fs::status(todoFile).permissions() */
/*     } else { */
/*         std::ofstream(todoFile.string()); // create file */
/*     } */
/* } */

int main(int argc, char** argv)
{
    fs::path todoFile(std::getenv("TODO_FILE") ?
            std::getenv("TODO_FILE") : "./todo_file");

    /* try { */
    /*     initialise(todoFile); */
    /* } catch (const std::exception& e) { */
    /*     std::cout << "Failed to initialise: " << e.what() << std::endl; */
    /*     return 1; */
    /* } */

    InputParser input{argc, argv};
    std::vector<TodoFunction*> functions;

    HelpFunction help{};

    functions.push_back(&help);
    functions.push_back(new AddFunction(input));

    help.addFunctions(functions);

    /* help.addFunction(new HelpFunction(input)); */

    if (input.isEmpty()) {
        std::cout << "PRINT TODOs" << std::endl;
    }
    else {
        for (auto const& func:functions) {
            if (input.hasOption(func->getName(), 0)) {
                func->run();
                return 0;
            }
        }
    }

    std::cout << "Unknown option: " <<
        std::quoted(input.getOption(0),'\'') << std::endl;

    return 1;
}
