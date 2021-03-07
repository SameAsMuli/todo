#ifndef ACTION_HELP_H
#define ACTION_HELP_H

#include <string> // std::string
#include <vector> // std::vector

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to display help information about the programme.
 */
class Help : public ActionAbstract {

  public:
    /**
     * @brief Initialise the help action.
     *
     * @param input The user's input.
     */
    Help(input::Input input);

    /**
     * @brief Get a detailed description of the help action.
     *
     * @return A string with the description of the help action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the help action.
     *
     * @return A string with the usage text of the help action.
     */
    std::string usage() const override;

    /**
     * @brief Set the list of functions and sort them alphabetically.
     *
     * @param functions A vector list of functions.
     */
    void addActions(std::vector<ActionAbstract *> &functions);

    /**
     * @brief Print the usage information for the program
     */
    void printGeneralUsage() const;

  private:
    std::vector<ActionAbstract *> m_actions;

    /**
     * @brief Print the help text and list all available functions.
     */
    void run() override;

    /**
     * @brief Sort function to order actions alphabetically by name.
     *
     * @param tf1 First action.
     * @param tf2 Second action.
     *
     * @return True if tf1 has a lower name than tf2.
     */
    static bool actionCompare(ActionAbstract *tf1, ActionAbstract *tf2);
};

#endif

} // namespace action
} // namespace todo
