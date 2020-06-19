#include <fstream>  // std::ofstream

#include "AddFunction.hpp"

AddFunction::AddFunction(
        const TodoFiles& todoFiles,
        const InputParser& input):
    TodoFunctionAbstract("add", "Add a normal priority TODO"),
    m_input(input),
    m_todoFiles(todoFiles)
{ }

void AddFunction::run()
{
    std::vector<std::string>::size_type index = 1;
    std::ofstream ofs{
        this->m_todoFiles.getNormal().string(),
        std::ios_base::app};

    if (ofs.is_open()) {
        while (this->m_input.hasOption(index)) {
            ofs << this->m_input.getOption(index++);
        }
        ofs << std::endl;
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}
