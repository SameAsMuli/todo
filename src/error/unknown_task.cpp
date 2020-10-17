#include "error/unknown_task.hpp"

namespace todo {
namespace error {

UnknownTask::UnknownTask()
    : std::runtime_error("Search string didn't match any TODOs") {}

} // namespace error
} // namespace todo
