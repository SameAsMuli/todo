#include "action/low.hpp"

namespace action {

Low::Low(const util::InputParser& input, const std::filesystem::path& file):
    AddAbstract( "low", "Add a low priority TODO", input, file, "-")
{ }

} // namespace action
