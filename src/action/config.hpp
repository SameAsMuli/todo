#ifndef ACTION_CONFIG_H
#define ACTION_CONFIG_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to query and modify program configuration.
 */
class Config : public ActionAbstract {

  public:
    /**
     * @brief Initialise the config action.
     */
    Config();

    /**
     * @brief Get a detailed description of the config action.
     *
     * @return A string with the description of the config action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the config action.
     *
     * @return A string with the usage text of the config action.
     */
    std::string usage() const override;

  private:
    /**
     * @brief Query or modify configuration.
     */
    void run(const input::Input &input) override;
};

#endif

} // namespace action
} // namespace todo
