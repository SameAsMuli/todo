#include <string>

#include "error/duplicate_task.hpp"

namespace todo {
namespace error {

DuplicateTask::DuplicateTask() : std::runtime_error("Task already exists") {}

} // namespace error
} // namespace todo
