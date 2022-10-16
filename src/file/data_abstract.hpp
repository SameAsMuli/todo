#ifndef FILE_DATA_ABSTRACT_H
#define FILE_DATA_ABSTRACT_H

#include <filesystem>

#include "file/definitions.hpp"
#include "file/file.hpp"

namespace todo {
namespace file {

/**
 * @brief Abstract class representing a data file.
 *
 * This class defines the object representation of a data file, allowing
 * simple serialization/de-serialization.
 */
class DataAbstract {

  public:
    /**
     * @brief Initialise a concrete instance of this class.
     *
     * @param fileType The data file type to read.
     * @param dir The directory to read the file from.
     *
     * @return An instance of a class derived from DataAbstract.
     */
    static DataAbstract *init(const File &fileType,
                              std::filesystem::path dir = get_todo_dir(false));

    /**
     * @brief Get the file path for this data file.
     *
     * @return A filesystem path to the data file.
     */
    std::filesystem::path get_file() const;

    /**
     * @brief Read the contents of the data file into this class.
     */
    void read();

    /**
     * @brief Write the contents of this class into its data file.
     */
    void write() const;

  protected:
    /**
     * @brief Abstract constructor for class representation of a data file.
     *
     * @param fileType The type of file being represented by this class.
     * @param dir The directory in which the data file is located.
     */
    DataAbstract(const File &fileType, const std::filesystem::path &dir);

    /**
     * @brief Create file and parent directories if required.
     */
    void initialise_file() const;

  private:
    File m_fileType;

    std::filesystem::path m_dir;

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
