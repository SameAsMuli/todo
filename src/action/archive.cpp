#include "action/archive.hpp"
#include "file/mutators.hpp"

namespace action {

Archive::Archive(util::Input input)
    : ActionAbstract("archive", "Archive all complete TODOs", input, 0) {}

void Archive::run() { todo::file::archive(0); }

} // namespace action
