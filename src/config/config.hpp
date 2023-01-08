#ifndef CONFIG_CONFIG_H
#define CONFIG_CONFIG_H

#include <mutex>    // std::lock_guard, std::mutex
#include <optional> // std::optional

#include "config/key.hpp"
#include "file/config.hpp"

namespace todo {
namespace config {

/**
 * @brief A singleton class for accessing program configuration.
 */
class Config {

  public:
    /**
     * @brief Initialise the singleton.
     */
    static void init();

    /**
     * @brief Get the value of a given configuration key.
     *
     * The function will look through all configuration files in the current
     * path, starting from the current directory and moving up to the global
     * directory. If the key is found, the function will stop looking. If the
     * key is not found in any of the configuration files, the default will be
     * used.
     *
     * @param key The configuration key to consider.
     * @param global Whether to consider global config only.
     */
    template <typename T> static T get(const Key &key, bool global = false) {
        auto file = find_file(key, global);
        if (file == nullptr)
            return default_value<T>(key);
        return file->get<T>(key);
    }

    /**
     * @brief Set the value of a given configuration.
     *
     * @param key The configuration key to set.
     * @param value The new value.
     * @param global Whether to set in the global todo configuration.
     */
    template <typename T>
    static void set(const Key &key, const T &value, bool global = false) {
        auto file = find_file(global);
        if (file == nullptr)
            throw std::runtime_error{"unable to locate config file"};
        file->set(key, value);
    }

    /**
     * @brief Get the current value as a string.
     *
     * @param key The configuration key to consider.
     * @param global Whether to consider global config only.
     *
     * @return A string representation of the current configuration value.
     */
    static std::string get_str(const Key &key, bool global = false);

    /**
     * @brief Set the value of a given configuration from a string value.
     *
     * @param key The configuration key to consider.
     * @param value The new value as a string.
     * @param global Whether to consider the global todo configuration.
     */
    static void set_str(const Key &key, const std::string &value,
                        bool global = false);

    /**
     * @brief Get the default value of a given configuration key.
     *
     * @param key The configuration key to consider.
     */
    template <typename T> static T default_value(const Key &key) {
        T value;
        key.default_value(value);
        return value;
    }

    /**
     * @brief Get the default value as a string.
     *
     * @param key The configuration key to consider.
     *
     * @return A string representation of the default configuration value.
     */
    static std::string default_str(const Key &key);

  private:
    inline static std::unique_ptr<Config> m_config;
    inline static std::mutex m_init_mutex;

    std::vector<std::shared_ptr<file::Config>> m_configFiles;

    /**
     * @brief Private constructor to ensure usage as a singleton.
     */
    Config();

    /**
     * @brief Get either the local or global config file.
     *
     * This function will initialise the files if they do not already exist.
     *
     * @param global Whether to look for the global file or not.
     *
     * @return The specified configuration file.
     */
    static std::shared_ptr<file::Config> find_file(bool global);

    /**
     * @brief Find the closest config file containing the given key.
     *
     * @param key The key to consider.
     * @param global Whether to consider global config only.
     *
     * @return An optional Config file, populated if a suitable file is found.
     */
    static std::shared_ptr<file::Config> find_file(const Key &key, bool global);
};

} // namespace config
} // namespace todo

using Config = todo::config::Config;
using ConfigKey = todo::config::Key;

#endif
