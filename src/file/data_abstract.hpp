#ifndef FILE_DATA_ABSTRACT_H
#define FILE_DATA_ABSTRACT_H

#include <filesystem>

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
     * @param global Whether to consider the local or global data file.
     *
     * @return An instance of a class derived from DataAbstract.
     */
    static DataAbstract *init(File fileType, bool global = false);

    /**
     * @brief Get the file path for this data file.
     *
     * @return A filesystem path to the data file.
     */
    std::filesystem::path getFile() const;

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
     * @param global Whether to consider the global or local data file.
     */
    DataAbstract(File fileType, bool global = false);

    /**
     * @brief Create file and parent directories if required.
     */
    void initialiseFile() const;

  private:
    File m_fileType;

    bool m_global;

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
    virtual void initialiseFile_derived() const {};
};

} // namespace file
} // namespace todo

#endif
