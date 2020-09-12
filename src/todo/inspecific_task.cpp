#include <string>

#include "todo/inspecific_task.hpp"

namespace todo {

InspecificTask::InspecificTask(unsigned int count):
    std::runtime_error("Search string matched " + std::to_string(count) +
            " TODOs, be more specific!")
{ }

} // namespace todo
