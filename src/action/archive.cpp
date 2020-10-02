#include "action/archive.hpp"
#include "todo/files.hpp"

namespace action {

Archive::Archive(util::Input input)
    : ActionAbstract("archive", "Archive all complete TODOs", input, 0) {}

void Archive::run() { todo::files::archive(0); }

} // namespace action
