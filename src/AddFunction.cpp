#include <fstream>  // std::ofstream

#include "AddFunction.hpp"

AddFunction::AddFunction(
        const fs::path& todoFile,
        const InputParser& input):
    TodoFunctionAbstract("add", "Add a normal priority task"),
    m_input(input),
    m_todoFile(todoFile)
{ }

void AddFunction::run()
{
    std::vector<std::string>::size_type index = 1;
    std::ofstream ofs{this->m_todoFile.string(), std::ios_base::app};

    if (ofs.is_open()) {
        while (this->m_input.hasOption(index)) {
            ofs << this->m_input.getOption(index++);
        }
        ofs << std::endl;
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}
