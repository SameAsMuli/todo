#ifndef ACTION_FILE_H
#define ACTION_FILE_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to list occurrences of the todo-string in current directory.
 */
class File : public ActionAbstract {

  public:
    /**
     * @brief Initialise the file action.
     */
    File();

    /**
     * @brief Get a detailed description of the file action.
     *
     * @return A string with the description of the file action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the file action.
     *
     * @return A string with the usage text of the file action.
     */
    std::string usage() const override;

  private:
    /**
     * @brief Find todo-string occurrences.
     */
    void run(const input::Input &input) override;
};

#endif

} // namespace action
} // namespace todo
