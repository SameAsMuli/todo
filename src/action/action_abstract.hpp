#ifndef ACTION_ACTION_ABSTRACT_H
#define ACTION_ACTION_ABSTRACT_H

#include <optional> //std::optional
#include <string>   // std::string
#include <vector>   // std::string

#include "input/input.hpp"
#include "input/option_type.hpp"

namespace todo {
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
     * @param validOptions The list of option types accepted by the action.
     * @param argLimit The maximum number of arguments the action allows.
     *
     * If no argLimit is given then a default of std::nullopt is used which
     * indicates that there is no limit.
     */
    ActionAbstract(const std::string &name, const std::string &helpText,
                   const input::Input &input,
                   std::vector<input::OptionType> validOptions = {},
                   std::optional<unsigned int> argLimit = std::nullopt);

    /**
     * @brief Get the name of the action.
     *
     * @return A string with the name of the action.
     */
    std::string getName() const { return m_name; }

    /**
     * @brief Get a short description of the action.
     *
     * This is used to give a brief, 1 line description of the action.
     *
     * @return A string with the short help text of the action.
     */
    std::string getHelpText() const { return m_helpText; }

    /**
     * @brief Get the input passed to the action.
     *
     * @return The Input object held by the aciton.
     */
    input::Input getInput() const { return m_input; }

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
     * @brief Get any additional aliases that can be used to access this action.
     *
     * @return An optional number of arguments.
     */
    std::vector<std::string> getAliases() const { return m_aliases; }

    /**
     * @brief Add another alias of this action.
     *
     * Aliases are other names that can be used to reference an action, besides
     * the default name accessed via getName().
     *
     * @param alias A string containing the alias to add.
     */
    void addAlias(const std::string &alias) { m_aliases.push_back(alias); }

    /**
     * @brief Check if the action is known by the given name.
     *
     * @param name The name to check against.
     *
     * @return True if the action name or any of its aliases match the input.
     */
    bool isKnownAs(const std::string &name) const;

    /**
     * @brief Check if the action can handle the given option.
     *
     * @param option The option to check.
     *
     * @return True if the action can handle the option, false otherwise.
     */
    bool acceptsOption(const input::OptionType &option) const;

    /**
     * @brief Get a detailed description of the action.
     *
     * This should provide a detailed, multi-line description of the action. It
     * should include information on any additional parameters that can be given
     * to the action.
     *
     * To be overriden in derived class.
     *
     * TODO-SAM Make description() a pure virutal function eventually.
     *
     * @return A string with the description of the action.
     */
    virtual std::string description() const { return ""; }

    /**
     * @brief Get the usage details of the action.
     *
     * This should provide details of any options or arguments that can be
     * passed to the action. This should be laid out according to the docopt
     * specification: docopt.org
     *
     * To be overriden in derived class.
     *
     * TODO-SAM Make usage() a pure virutal function eventually.
     *
     * @return A string with the usage text of the action.
     */
    virtual std::string usage() const { return ""; }

    /**
     * @brief Perform the main function of the todo action.
     *
     * Verify the number of arguments given before calling the run function.
     */
    void perform();

  private:
    const std::string m_name;

    const std::string m_helpText;

    const input::Input m_input;

    const std::optional<unsigned int> m_argLimit;

    std::vector<std::string> m_aliases;

    const std::vector<input::OptionType> m_validOptions;

    /**
     * @brief Function that describes how the action should behave.
     *
     * To be overriden in derived class.
     */
    virtual void run() = 0;
};

} // namespace action
} // namespace todo

#endif
