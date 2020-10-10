#ifndef UTIL_INPUT_H
#define UTIL_INPUT_H

#include <string> // std::string
#include <vector> // std::vector

namespace util {

/**
 * @brief Contain and access the input given by the user.
 *
 * TODO-SAM Use SafeInt with size_type parameters to prevent underflow.
 */
class Input {

  public:
    /**
     * @brief Take user input from main and store in this class.
     *
     * @param argc The argument count from main.
     * @param argv The list of given arguments from main.
     */
    Input(int argc, char const *const *argv);

    /**
     * @brief Indicates the index containing the action name.
     */
    static const std::vector<std::string>::size_type ACTION_INDEX;

    /**
     * @brief Indicates the index at which action arguments start.
     */
    static const std::vector<std::string>::size_type PARAM_START_INDEX;

    /**
     * @brief Find the number of separate inputs given.
     *
     * @return The size type of the vector containing the inputs.
     */
    std::vector<std::string>::size_type size() const;

    /**
     * @brief Return whether any inputs were given.
     *
     * @return True if no inputs, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Return whether a given option is in the inputs.
     *
     * @param option The option to search for.
     *
     * @return True if inputs contain the option, false otherwise.
     */
    bool hasOption(const std::string &option) const;

    /**
     * @brief Return whether the vector of inputs has a specific index.
     *
     * @param index The index to check.
     *
     * @return True if the index exists, false otherwise.
     */
    bool hasOption(std::vector<std::string>::size_type index) const;

    /**
     * @brief Return whether the nth input is a specific option.
     *
     * @param option The option to check against.
     * @param index The index to check.
     *
     * @return True if the index equals option, false otherwise.
     */
    bool hasOption(const std::string &option,
                   std::vector<std::string>::size_type index) const;

    /**
     * @brief Get the option from a given index in the vector of inputs.
     *
     * @param index The index to check.
     *
     * @return The option at the given index.
     */
    std::string getOption(std::vector<std::string>::size_type index) const;

    /**
     * @brief Format the vector as string from a given index.
     *
     * @param index The first index to be included in the string.
     *
     * @return A space separated string of the vector.
     */
    std::string toString(std::vector<std::string>::size_type index) const;

  private:
    std::vector<std::string> m_tokens;
};

} // namespace util

#endif
