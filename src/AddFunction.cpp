#include <fstream>  // std::ofstream

#include "AddFunction.hpp"

AddFunction::AddFunction(fs::path todoFile, InputParser& input):
    TodoFunctionAbstract("add", "Add a normal priority task"),
    mInput(input),
    mTodoFile(todoFile)
{ }

void AddFunction::run()
{
    std::vector<std::string>::size_type index = 1;
    std::ofstream ofs{this->mTodoFile.string(), std::ios_base::app};

    if (ofs.is_open()) {
        while (this->mInput.hasOption(index)) {
            ofs << this->mInput.getOption(index++);
        }
        ofs << std::endl;
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}
