#ifndef ACTION_VIEW_H
#define ACTION_VIEW_H

#include <filesystem> //std::filesystem

#include "action/action_abstract.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to view different task types.
 */
class View : public ActionAbstract {

  public:
    /**
     * @brief Initialise the view action.
     */
    View();

    /**
     * @brief Print all todo tasks.
     *
     * If the action has an empty input, all task types are printed. If the
     * input is non-empty, the input will be matched against a task type and
     * that type will be printed. If the input cannot be matched to a task type
     * then an exception will be thrown.
     *
     * @param input The user's input.
     */
    void run(const input::Input &input) override;

    /**
     * @brief Print all complete tasks.
     *
     * @param input The user's input.
     */
    void completeTodos(input::Input input) const;

    /**
     * @brief Print all outstanding tasks.
     *
     * @param input The user's input.
     */
    void outstandingTodos(input::Input input) const;

    /**
     * @brief Print all done tasks.
     *
     * @param input The user's input.
     */
    void doneTodos(input::Input input) const;

    /**
     * @brief Print all high tasks.
     *
     * @param input The user's input.
     */
    void highTodos(input::Input input) const;

    /**
     * @brief Print all low priority tasks.
     *
     * @param input The user's input.
     */
    void lowTodos(input::Input input) const;

    /**
     * @brief Print all normal priority tasks.
     *
     * @param input The user's input.
     */
    void normalTodos(input::Input input) const;

    /**
     * @brief Print all rejected tasks.
     *
     * @param input The user's input.
     */
    void rejectTodos(input::Input input) const;

    /**
     * @brief Print all urgent tasks.
     *
     * @param input The user's input.
     */
    void urgentTodos(input::Input input) const;
};

#endif

} // namespace action
} // namespace todo
