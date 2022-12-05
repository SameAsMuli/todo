#ifndef FILE_FILE_ABSTRACT_H
#define FILE_FILE_ABSTRACT_H

#include <filesystem>

#include "file/definitions.hpp"
#include "file/file.hpp"

namespace todo {
namespace file {

/**
 * @brief Abstract class representing a todo file.
 *
 * This class defines the object representation of a todo file, allowing
 * simple serialization/de-serialization.
 */
class FileAbstract {

  public:
    /**
     * @brief Initialise a concrete instance of this class.
     *
     * @param fileType The todo file type to read.
     * @param dir The directory to read the file from.
     *
     * @return An instance of a class derived from FileAbstract.
     */
    static FileAbstract *
    init(const File &fileType,
         const std::filesystem::path &dir = get_todo_dir(false));

    /**
     * @brief Get the file path for this todo file.
     *
     * @return A filesystem path to the todo file.
     */
    std::filesystem::path get_file() const;

    /**
     * @brief Get the todo directory that stores this file.
     *
     * @return A filesystem path to the todo directory containing this file.
     */
    std::filesystem::path get_dir() const { return m_dir; }

    /**
     * @brief Read the contents of the todo file into this class.
     */
    void read();

    /**
     * @brief Write the contents of this class into its todo file.
     */
    void write() const;

  protected:
    /**
     * @brief Abstract constructor for class representation of a todo file.
     *
     * @param fileType The type of file being represented by this class.
     * @param dir The directory in which the todo file is located.
     * @param sub_dir Any sub-directories below the main todo directory.
     */
    FileAbstract(
        const File &fileType, const std::filesystem::path &dir,
        const std::filesystem::path &sub_dir = std::filesystem::path{});

    /**
     * @brief Virtual destructor for class.
     */
    virtual ~FileAbstract() = 0;

    /**
     * @brief Create file and parent directories if required.
     */
    void initialise_file() const;

  private:
    File m_fileType;

    std::filesystem::path m_dir;

    std::filesystem::path m_sub_dir;

    /**
     * @brief Allow derived classes to perform specific read actions.
     */
    virtual void read_derived() = 0;

    /**
     * @brief Allow derived classes to perform specific write actions.
     */
    virtual void write_derived() const = 0;

    /**
     * @brief Allow derived classes to perform specific initialisation actions.
     */
    virtual void initialise_file_derived() const {};
};

} // namespace file
} // namespace todo

#endif
