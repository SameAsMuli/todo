#ifndef ACTION_SEARCH_H
#define ACTION_SEARCH_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to search a task.
 */
class Search : public ActionAbstract {

  public:
    /**
     * @brief Initialise the search action.
     */
    Search();

    /**
     * @brief Get a detailed description of the search action.
     *
     * @return A string with the description of the search action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the search action.
     *
     * @return A string with the usage text of the search action.
     */
    std::string usage() const override;

  private:
    /**
     * @brief Search matching task.
     */
    void run(const input::Input &input) override;
};

#endif

} // namespace action
} // namespace todo
