#ifndef TASK_PREFIX_H
#define TASK_PREFIX_H

#include <iostream> // std::istream, std::ostream

namespace todo {
namespace task {

/**
 * @brief Class to represent a task prefix.
 *
 * Main intention is to allow an unknown or uninitialised prefix to be
 * specified via the NULL_PREFIX character.
 */
class Prefix {

  public:
    /**
     * @brief Indicates a lack of prefix character.
     */
    static const char NULL_PREFIX;

    /**
     * @brief Construct a prefix with a NULL_PREFIX character.
     */
    Prefix();

    /**
     * @brief Construct the prefix with a given character.
     *
     * @param character The character for this prefix.
     */
    Prefix(char character);

    /**
     * @brief Set the character for the prefix.
     *
     * @param character The character to use.
     */
    void setCharacter(char character);

    /**
     * @brief Check if two prefix objects have the same character.
     *
     * @param prefix The other prefix to check.
     *
     * @return True if the characters are the same, false otherwise.
     */
    bool operator==(Prefix prefix);

    /**
     * @brief Populate the prefix from a stream.
     *
     * Takes the first character from the stream and uses that as the prefix
     * character. If that character is '\0' or whitespace then NULL_PREFIX is
     * used.
     *
     * @param stream The stream to use.
     * @param prefix The prefix object to populate.
     *
     * @return The given stream.
     */
    friend std::istream &operator>>(std::istream &stream, Prefix &prefix);

    /**
     * @brief Output a prefix character to a given stream.
     *
     * @param stream The stream to use.
     * @param prefix The prefix to use.
     *
     * @return The given stream.
     */
    friend std::ostream &operator<<(std::ostream &stream, const Prefix &prefix);

  private:
    char m_character;
};

} // namespace task
} // namespace todo

#endif
