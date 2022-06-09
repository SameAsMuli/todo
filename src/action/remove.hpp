#ifndef ACTION_REMOVE_H
#define ACTION_REMOVE_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to remove a task.
 */
class Remove : public ActionAbstract {

  public:
    /**
     * @brief Initialise the remove action.
     */
    Remove();

    /**
     * @brief Get a detailed description of the remove action.
     *
     * @return A string with the description of the remove action.
     */
    std::string description() const override;

    /**
     * @brief Remove matching task.
     */
    void run(const input::Input &input) override;
};

#endif

} // namespace action
} // namespace todo
