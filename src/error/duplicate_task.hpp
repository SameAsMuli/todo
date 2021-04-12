#ifndef TODO_ERROR_DUPLICATE_TASK_H
#define TODO_ERROR_DUPLICATE_TASK_H

#include <stdexcept> // std::runtime_error

namespace todo {
namespace error {

/**
 * @brief Error for receiving task that already exists.
 */
class DuplicateTask : public std::runtime_error {

  public:
    /**
     * @brief Error for a pre-existing task.
     */
    DuplicateTask();
};

} // namespace error
} // namespace todo

#endif
