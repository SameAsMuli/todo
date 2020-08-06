#include <fstream>  // std::ofstream

#include "action/add.hpp"

namespace action {

AddAbstract::AddAbstract(
        const std::string&           name,
        const std::string&           helpText,
        const util::InputParser&     input,
        const std::filesystem::path& file,
        const std::string&           prefix):
    ActionAbstract(name, helpText),
    m_input(input),
    m_file(file),
    m_prefix(prefix)
{ }

void AddAbstract::run()
{
    std::vector<std::string>::size_type index = 1;
    std::ofstream ofs{
        this->m_file.string(),
        std::ios_base::app};

    if (ofs.is_open()) {
        ofs << this->getPrefix();
        while (this->m_input.hasOption(index)) {
            ofs << " " << this->m_input.getOption(index++);
        }
        ofs << std::endl;
    } else {
        throw std::runtime_error("Unable to open TODO file");
    }
}

} // namespace action
