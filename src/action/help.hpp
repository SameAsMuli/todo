#ifndef ACTION_HELP_H
#define ACTION_HELP_H

#include <vector> // std::vector

#include "action/action_abstract.hpp"
#include "util/input.hpp"

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
    Help(util::Input input);

    /**
     * @brief Print the help text and list all available functions.
     */
    void run() override;

    /**
     * @brief Set the list of functions and sort them alphabetically.
     *
     * @param functions A vector list of functions.
     */
    void addFunctions(std::vector<ActionAbstract *> &functions);

  private:
    std::vector<ActionAbstract *> m_functions;

    /**
     * @brief Sort function to order actions alphabetically by name.
     *
     * @param tf1 First action.
     * @param tf2 Second action.
     *
     * @return True if tf1 has a lower name than tf2.
     */
    static bool todoFuncComp(ActionAbstract *tf1, ActionAbstract *tf2);
};

#endif

} // namespace action
} // namespace todo
