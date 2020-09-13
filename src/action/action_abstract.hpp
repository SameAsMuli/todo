#ifndef ACTION_ACTION_ABSTRACT_H
#define ACTION_ACTION_ABSTRACT_H

#include <optional> //std::optional
#include <string>   // std::string

#include "util/input.hpp"

namespace action {

/**
 * @brief Defines the basic interface and members for an action.
 */
class ActionAbstract {

  public:
    /**
     * @brief Base constructor for an action.
     *
     * @param name The name of the action.
     * @param helpText A short description of the action.
     * @param input The user's input to be passed to the action.
     * @param argLimit The maximum number of arguments the action allows.
     *
     * If no argLimit is given then a default of std::nullopt is used which
     * indicates that there is no limit.
     */
    ActionAbstract(const std::string &name, const std::string &helpText,
                   const util::Input &input,
                   std::optional<unsigned int> argLimit = std::nullopt);

    /**
     * @brief Get the name of the action.
     *
     * @return A string with the name of the action.
     */
    std::string getName() const { return m_name; }

    /**
     * @brief Get the help text of the action.
     *
     * @return A string with the help text of the action.
     */
    std::string getHelpText() const { return m_helpText; }

    /**
     * @brief Get the input passed to the action.
     *
     * @return The Input object held by the aciton.
     */
    util::Input getInput() const { return m_input; }

    /**
     * @brief Get the maximum number of arguments allowed for the action.
     *
     * If there is no limit to the allowed number of arguments, std::nullopt is
     * returned.
     *
     * @return An optional number of arguments.
     */
    std::optional<unsigned int> getArgLimit() const { return m_argLimit; }

    /**
     * @brief Perform the main function of the todo action.
     *
     * Verify the number of arguments given before calling the run function.
     */
    void perform();

  private:
    const std::string m_name;

    const std::string m_helpText;

    const util::Input m_input;

    const std::optional<unsigned int> m_argLimit;

    /**
     * @brief Function that describes how the action should behave.
     *
     * To be overriden in derived class.
     */
    virtual void run() = 0;
};

} // namespace action

#endif
