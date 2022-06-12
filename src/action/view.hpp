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
     * @brief Get a detailed description of the archive action.
     *
     * @return A string with the description of the archive action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the archive action.
     *
     * @return A string with the usage text of the archive action.
     */
    std::string usage() const override;
};

#endif

} // namespace action
} // namespace todo
