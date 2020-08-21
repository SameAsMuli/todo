#include "action/add.hpp"

namespace action {

Add::Add(const util::Input& input, const std::filesystem::path& file):
    AddAbstract( "add", "Add a normal priority TODO", input, file, "-")
{ }

} // namespace action
