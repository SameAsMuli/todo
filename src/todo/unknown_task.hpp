#ifndef TODO_UNKNOWN_TASK_H
#define TODO_UNKNOWN_TASK_H

#include <stdexcept> // std::runtime_error

namespace todo {

/**
 * @brief Error for receiving an unrecognised task description from the user.
 */
class UnknownTask : public std::runtime_error {

  public:
    /**
     * @brief Error that there are no tasks matched by the given description.
     */
    UnknownTask();
};

} // namespace todo

#endif
