#include <string>

#include "error/inspecific_task.hpp"

namespace todo {
namespace error {

InspecificTask::InspecificTask(unsigned int count)
    : std::runtime_error("Search string matched " + std::to_string(count) +
                         " TODOs, be more specific!") {}

} // namespace error
} // namespace todo
