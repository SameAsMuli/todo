#include "action/archive.hpp"
#include "file/mutators.hpp"

namespace todo {
namespace action {

Archive::Archive(util::Input input)
    : ActionAbstract("archive", "Archive all complete TODOs", input, 0) {}

void Archive::run() { file::archive(0); }

} // namespace action
} // namespace todo
