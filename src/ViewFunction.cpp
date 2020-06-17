#include <fstream>  // std::ifstream
#include <iostream> // std::cerr

#include "ViewFunction.hpp"

ViewFunction::ViewFunction(
        const fs::path& todoFile,
        const InputParser& input):
    TodoFunctionAbstract("view", "View outstanding TODOs"),
    m_input(input),
    m_todoFile(todoFile)
{ }

void ViewFunction::run()
{
    std::ifstream ifs{this->m_todoFile.string()};

    if (ifs.is_open()) {
        std::cout << ifs.rdbuf();
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}
