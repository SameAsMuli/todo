#ifndef ACTION_ACTION_ABSTRACT_H
#define ACTION_ACTION_ABSTRACT_H

#include <optional>      //std::optional
#include <string>        // std::string
#include <unordered_set> // std::unordered_set

#include "config/config.hpp"
#include "input/input.hpp"
#include "input/option.hpp"

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
     * @param argLimit The maximum number of arguments the action allows.
     *
     * If no argLimit is given, then a default of std::nullopt is used. This is
     * used to indicate that there is no limit.
     */
    ActionAbstract(const std::string &name, const std::string &helpText,
                   std::optional<unsigned int> argLimit = std::nullopt);

    /**
     * @brief Base destructor for an action.
     */
    virtual ~ActionAbstract() = default;

    /**
     * @brief Get the name of the action.
     *
     * @return A string with the name of the action.
     */
    std::string get_name() const { return m_name; }

    /**
     * @brief Get a short description of the action.
     *
     * This is used to give a brief, 1 line description of the action.
     *
     * @return A string with the short help text of the action.
     */
    std::string get_help_text() const { return m_helpText; }

    /**
     * @brief Get the maximum number of arguments allowed for the action.
     *
     * If there is no limit to the allowed number of arguments, std::nullopt is
     * returned.
     *
     * @return An optional number of arguments.
     */
    std::optional<unsigned int> get_arg_limit() const { return m_argLimit; }

    /**
     * @brief Get any additional aliases that can be used to access this action.
     *
     * @return A set of string aliases for this action.
     */
    std::unordered_set<std::string> get_aliases() const { return m_aliases; }

    /**
     * @brief Add another alias of this action.
     *
     * Aliases are other names that can be used to reference an action, besides
     * the default name accessed via get_name().
     *
     * @param alias A string containing the alias to add.
     */
    void add_alias(const std::string &alias);

    /**
     * @brief Check if the action is known by the given name.
     *
     * @param name The name to check against.
     *
     * @return True if the action name or any of its aliases match the input.
     */
    bool is_known_as(const std::string &name) const;

    /**
     * @brief Get any options that can be used to with this action.
     *
     * @return A set of options that can be used with this action.
     */
    std::unordered_set<input::Option> get_valid_options() const {
        return m_validOptions;
    }

    /**
     * @brief Get any configuration keys whose behaviour relates to this action.
     *
     * @return A set of ConfigKeys that relate to this action.
     */
    std::unordered_set<ConfigKey> get_related_config() const {
        return m_relatedConfig;
    }

    /**
     * @brief Add an option to the list of accepted options for this action.
     *
     * @param option The option to mark as valid.
     */
    void add_valid_option(const input::Option &option);

    /**
     * @brief Add a configuration key to the related keys for this action.
     *
     * @param key The key to mark as related.
     */
    void add_related_config(const ConfigKey &key);

    /**
     * @brief Check if the action can handle the given option.
     *
     * @param option The option to check.
     *
     * @return True if the option is valid for the action, false otherwise.
     */
    bool valid_option(const input::Option &option) const;

    /**
     * @brief Print general information about the action.
     */
    void print_details() const;

    /**
     * @brief Get a detailed description of the action.
     *
     * This should provide a detailed, multi-line description of the action. It
     * should include information on any additional parameters that can be given
     * to the action.
     *
     * To be overriden in derived class.
     *
     * @return A string with the description of the action.
     */
    virtual std::string description() const = 0;

    /**
     * @brief Get the usage details of the action.
     *
     * This should provide details of any options or arguments that can be
     * passed to the action. This should be laid out according to the docopt
     * specification: docopt.org
     *
     * To be overriden in derived class.
     *
     * @return A string with the usage text of the action.
     */
    virtual std::string usage() const = 0;

    /**
     * @brief Perform the main function of the todo action.
     *
     * Verify the number of arguments given before calling the run function.
     *
     * @param input The user's input to be passed to the action.
     */
    void perform(const input::Input &input);

  private:
    const std::string m_name;

    const std::string m_helpText;

    const std::optional<unsigned int> m_argLimit;

    std::unordered_set<std::string> m_aliases;

    std::unordered_set<input::Option> m_validOptions;

    std::unordered_set<ConfigKey> m_relatedConfig;

    /**
     * @brief Function that describes how the action should behave.
     *
     * To be overriden in derived class.
     *
     * @param input The user's input to be passed to the action.
     */
    virtual void run(const input::Input &input) = 0;
};

} // namespace action
} // namespace todo

#endif
