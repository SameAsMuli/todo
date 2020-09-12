#include "todo/unknown_task.hpp"

namespace todo {

UnknownTask::UnknownTask()
    : std::runtime_error("Search string didn't match any TODOs") {}

} // namespace todo
