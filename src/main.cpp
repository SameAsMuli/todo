#include <cstdlib>    // std::getenv
#include <exception>  // std::exception
#include <filesystem> // std::filesystem
#include <iostream>   // std::cout
#include <string>     // std::string

#include "InputParser.hpp"
#include "TodoFunction.hpp"

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

void printHelpInfo() {
    std::cout << "TODO Management Utility" << std::endl;
    std::cout << std::endl;
    std::cout << "If run with no arguments will print all TODOs found" << std::endl;
    std::cout << "in the todo file." << std::endl;
    std::cout << std::endl;
    std::cout << "Value of the todo file defaults to '~/.config/todo'" << std::endl;
    std::cout << "but can be overriden using $TODO_FILE." << std::endl;
    std::cout << std::endl;
    std::cout << "List of commands:" << std::endl;
    std::cout << "  help ...... Display this help text" << std::endl;
    std::cout << std::endl;
    std::cout << "Written by Sam Amis" << std::endl;
}

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

    InputParser input(argc, argv);

    /* Use array of "input" structs that can be iterated over for help text */
    if (input.isEmpty()) {
        std::cout << "PRINT TODOs" << std::endl;
    }
    else if (input.hasOption("help")) {
        printHelpInfo();
    }
    else if (input.hasOption("add", 0)) {
        std::cout << "ADD" << std::endl;
    }
    else {
        std::cout << "UNKNOWN OPTIONS" << std::endl;
    }

    return 0;
}
