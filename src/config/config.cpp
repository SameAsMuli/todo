#include "config/config.hpp"

namespace todo {
namespace config {

void Config::init() {
    std::lock_guard<std::mutex> guard{m_init_mutex};
    if (m_config == nullptr)
        m_config.reset(new Config{});
}

std::string Config::get_str(const Key &key) {
    switch (key.type()) {
    case integer:
        return std::to_string(get<int>(key));
    case string:
        return get<std::string>(key);
    default:
        return "";
    }
}

std::string Config::default_str(const Key &key) {
    switch (key.type()) {
    case integer:
        return std::to_string(default_value<int>(key));
    case string:
        return "'" + default_value<std::string>(key) + "'";
    default:
        return "";
    }
}

std::optional<file::Config> Config::find_file(const Key &key) {
    /* Initialise the class if this is the first time calling it */
    if (m_config == nullptr)
        init();

    for (const auto &dir : file::get_local_todo_dir_hierarchy()) {
        auto config = file::Config(dir);
        if (!config.has_key(key))
            continue;
        return config;
    }
    return std::nullopt;
}

} // namespace config
} // namespace todo
