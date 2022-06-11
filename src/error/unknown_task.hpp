#ifndef TODO_ERROR_UNKNOWN_TASK_H
#define TODO_ERROR_UNKNOWN_TASK_H

#include <stdexcept> // std::runtime_error

namespace todo {
namespace error {

/**
 * @brief Error for receiving an unrecognised task description from the user.
 */
class UnknownTask : public std::runtime_error {

  public:
    /**
     * @brief Error that there are no tasks matched by the given description.
     */
    UnknownTask()
        : std::runtime_error("Search string didn't match any TODOs") {}
};

} // namespace error
} // namespace todo

#endif
