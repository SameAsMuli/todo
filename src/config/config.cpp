#include "config/config.hpp"

namespace todo {
namespace config {

void Config::init() {
    std::lock_guard<std::mutex> guard{m_init_mutex};
    if (m_config == nullptr)
        m_config.reset(new Config{});
}

std::string Config::get_str(const Key &key, bool global) {
    switch (key.type()) {
    case integer:
        return std::to_string(get<int>(key, global));
    case string:
        return get<std::string>(key, global);
    default:
        return "";
    }
}

std::string Config::default_str(const Key &key) {
    switch (key.type()) {
    case integer:
        return std::to_string(default_value<int>(key));
    case string:
        return default_value<std::string>(key);
    default:
        return "";
    }
}

void Config::set_str(const Key &key, const std::string &value, bool global) {
    switch (key.type()) {
    case integer:
        set(key, std::stoi(value), global);
        break;
    case string:
        set(key, value, global);
        break;
    default:
        break;
    }
}

Config::Config() {
    for (const auto &dir : file::get_local_todo_dir_hierarchy()) {
        this->m_configFiles.push_back(std::make_shared<file::Config>(dir));
    }
}

std::shared_ptr<file::Config> Config::find_file(bool global) {
    /* Initialise the class if this is the first time calling it */
    if (m_config == nullptr)
        init();

    auto fileList = m_config->m_configFiles;
    if (fileList.empty())
        return nullptr;

    if (global)
        return m_config->m_configFiles.back();

    /* The local todo directory may not exist, add it if needed */
    auto localDir = file::get_local_todo_dir_name();
    auto firstFile = fileList.front();

    if (std::filesystem::exists(localDir) &&
        std::filesystem::equivalent(firstFile->get_dir(), localDir))
        return firstFile;

    firstFile = std::make_shared<file::Config>(localDir);
    fileList.insert(fileList.begin(), firstFile);
    return firstFile;
}

std::shared_ptr<file::Config> Config::find_file(const Key &key, bool global) {
    /* Initialise the class if this is the first time calling it */
    if (m_config == nullptr)
        init();

    auto fileList = m_config->m_configFiles;
    if (fileList.empty())
        return nullptr;

    /* Only check the global file if indicated */
    if (global) {
        auto globalFile = fileList.back();
        if (globalFile->has_key(key))
            return globalFile;
        return nullptr;
    }

    /* Otherwise look up through the todo hierarchy */
    for (const auto &file : fileList) {
        if (file->has_key(key))
            return file;
    }

    return nullptr;
}

} // namespace config
} // namespace todo
