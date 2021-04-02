#ifndef INPUT_INPUT_H
#define INPUT_INPUT_H

#include <map>    // std::map
#include <string> // std::string
#include <vector> // std::vector

#include "input/option_type.hpp"

namespace input {

/**
 * @brief Contain and access the input given by the user.
 */
class Input {

  public:
    /**
     * @brief Default constructor.
     */
    Input() {}

    /**
     * @brief Take user input from main and store in this class.
     *
     * @param argc The argument count from main.
     * @param argv The list of given arguments from main.
     */
    Input(int argc, char const *const *argv);

    /**
     * @brief Get the action string from the input.
     *
     * @return The action name or empty string if not available.
     */
    std::string getAction() const { return m_action; }

    /**
     * @brief Get a specific action argument.
     *
     * @param index The index to check.
     *
     * @return The action argument at the given index.
     */
    std::string getActionArg(int index) const;

    /**
     * @brief Get all arguments passed to the action.
     *
     * @return A vector of string arguments passed to the action.
     */
    std::vector<std::string> getActionArgs() const { return m_actionArgs; }

    /**
     * @brief Format the action arguments as a single string.
     *
     * @param index The first index to be included in the string.
     *
     * @return A space separated string of all the action arguments.
     */
    std::string getActionArgString(int index = 0) const;

    /**
     * @brief Return whether the action arguments vector has a specific index.
     *
     * @param index The index to check.
     *
     * @return True if the index exists, false otherwise.
     */
    bool hasActionArg(int index) const;

    /**
     * @brief Return whether a given string is in the action arguments.
     *
     * @param arg The string argument to search for.
     *
     * @return True if inputs contain the arg, false otherwise.
     */
    bool hasActionArg(const std::string &arg) const;

    /**
     * @brief Return whether the nth input is a specific string.
     *
     * @param arg The argument string to check against.
     * @param index The index to check.
     *
     * @return True if the index equals arg, false otherwise.
     */
    bool hasActionArg(const std::string &arg, int index) const;

    /**
     * @brief Return whether a specific option type was specified.
     *
     * @param optionType The option type to check for.
     *
     * @return True if the option type is found, false otherwise.
     */
    bool hasOption(const OptionType &optionType) const;

    /**
     * @brief Get all arguments passed to a specific option type.
     *
     * @param optionType The option type to consider.
     *
     * @return A vector of string arguments passed to the option type.
     */
    std::vector<std::string> getOptionArgs(const OptionType &optionType) const;

  private:
    std::string m_action;

    std::vector<std::string> m_actionArgs;

    std::map<OptionType, std::vector<std::string>> m_options;
};

} // namespace input

#endif