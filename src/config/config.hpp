#ifndef CONFIG_CONFIG_H
#define CONFIG_CONFIG_H

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
     */
    template <typename T> static T get(const Key &key) {
        T value;
        auto config = find_file(key);

        if (config.has_value())
            config.value().get(key, value);
        else
            key.default_value(value);

        return value;
    }

  private:
    inline static std::unique_ptr<Config> m_config;
    inline static std::mutex m_init_mutex;

    /**
     * @brief Find the closest config file containing the given key.
     *
     * @param key The key to consider.
     *
     * @return An optional Config file, populated if a suitable file is found.
     */
    static std::optional<file::Config> find_file(const Key &key);
};

} // namespace config
} // namespace todo

#endif
