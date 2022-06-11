#ifndef TODO_ERROR_INSPECIFIC_TASK_H
#define TODO_ERROR_INSPECIFIC_TASK_H

#include <stdexcept> // std::runtime_error
#include <string>    // std::to_string

namespace todo {
namespace error {

/**
 * @brief Error for receiving too vague a task description from the user.
 */
class InspecificTask : public std::runtime_error {

  public:
    /**
     * @brief Error with the number of tasks matched by the given description.
     *
     * @param count The number of tasks matched.
     */
    InspecificTask(unsigned int count)
        : std::runtime_error("Search string matched " + std::to_string(count) +
                             " TODOs, be more specific!") {}
};

} // namespace error
} // namespace todo

#endif
