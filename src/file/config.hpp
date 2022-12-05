#ifndef FILE_CONFIG_H
#define FILE_CONFIG_H

#include <functional> // std::function

#include "config/json.hpp"
#include "config/key.hpp"
#include "file/file_abstract.hpp"

namespace todo {
namespace file {

/**
 * @brief Class representing a configuration file.
 *
 * This class defines the object representation of a config file, allowing
 * simple serialization/de-serialization between itself and the file.
 */
class Config : public FileAbstract {

  public:
    /**
     * @brief Construct the class, referencing a specific config file.
     *
     * This function will read the file and populate this class with the
     * contents.
     *
     * @param dir The directory to read the file from.
     */
    explicit Config(const std::filesystem::path &dir = get_todo_dir(false));

    /**
     * @brief Destructor for the Configuration.
     *
     * Will write the internal state of the class to the linked file.
     */
    ~Config();

    /**
     * @brief Check if the config file contains the given Key.
     *
     * @param key The key to search for.
     *
     * @return True if the key is found, false otherwise.
     */
    bool has_key(const config::Key &key) const;

    /**
     * @brief Get the value of a given configuration key.
     *
     * This function assumes the key already exists in the configuration.
     *
     * @param key The configuration key to consider.
     *
     * @return The value of the configuration.
     */
    template <typename T> T get(const config::Key &key) const {
        return m_json_config[key.to_string()];
    }

    /**
     * @brief Set the value of a given configuration key.
     *
     * @param key The configuration key to consider.
     * @param value The new value.
     */
    template <typename T> void set(const config::Key &key, const T &value) {
        m_json_config[key.to_string()] = value;
    }

  private:
    JSON m_json_config;
    /**
     * @brief Read the config file into this class instance.
     */
    void read_derived() override;

    /**
     * @brief Write this class's data to the config file.
     */
    void write_derived() const override;

    /**
     * @brief Put an empty array in the config file if it's currently empty.
     */
    void initialise_file_derived() const override;
};

} // namespace file
} // namespace todo

#endif
