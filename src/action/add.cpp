#include <fstream>  // std::ofstream

#include "action/add.hpp"
#include "env/todofiles.hpp"

namespace action {

Add::Add(const util::InputParser& input):
    ActionAbstract("add", "Add a normal priority TODO"),
    m_input(input)
{ }

void Add::run()
{
    std::vector<std::string>::size_type index = 1;
    std::ofstream ofs{
        TodoFiles::getNormal().string(),
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

} // namespace action
