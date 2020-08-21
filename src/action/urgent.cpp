#include "action/urgent.hpp"

namespace action {

Urgent::Urgent(const util::Input& input,
        const std::filesystem::path& file):
    AddAbstract( "urgent", "Add an urgent priority TODO", input, file, "!")
{ }

} // namespace action
