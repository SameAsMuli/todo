#ifndef ACTION_VERSION_H
#define ACTION_VERSION_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to display version information about the programme.
 */
class Version : public ActionAbstract {

  public:
    /**
     * @brief Initialise the version action.
     *
     * @param input The user's input.
     */
    Version(input::Input input);

    /**
     * @brief Get a detailed description of the version action.
     *
     * @return A string with the description of the version action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the version action.
     *
     * @return A string with the usage text of the version action.
     */
    std::string usage() const override;

  private:
    /**
     * @brief Print the version information.
     */
    void run() override;
};

#endif

} // namespace action
} // namespace todo
