#include <fstream> // std::ofstream

#include "env/todofiles.hpp"
#include "task/outstanding_abstract.hpp"

namespace task {

OutstandingAbstract::OutstandingAbstract(char prefix):
    TaskTypeAbstract(TodoFiles::getOutstanding(), prefix)
{ }

void OutstandingAbstract::add(const util::Input& input)
{
    auto description = input.toString(util::Input::PARAM_START_INDEX);
    if (description.empty()) {
        throw std::logic_error{"Empty input passed to add method"};
    }

    std::ofstream ofs{this->getFile().string(), std::ios_base::app};
    if (ofs.is_open()) {
        ofs << this->getPrefix() << " " << description << std::endl;
    } else {
        throw std::runtime_error{"Unable to open TODO file"};
    }
}

} // namespace task
