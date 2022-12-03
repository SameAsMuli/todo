#include <fstream> // std::ifstream, std::ofstream

#include "error/invalid_config.hpp"
#include "file/config.hpp"

namespace todo {
namespace file {

Config::Config(const std::filesystem::path &dir)
    : FileAbstract(File::config, dir) {
    read();
}

bool Config::has_key(const config::Key &key) const {
    return m_json_config.contains(key.to_string());
}

void Config::get(const config::Key &key, int &value) const {
    value = m_json_config[key.to_string()];
}

void Config::get(const config::Key &key, std::string &value) const {
    value = m_json_config[key.to_string()];
}

void Config::read_derived() {
    auto filePathStr = get_file().string();

    std::ifstream fileStream{filePathStr};

    try {
        fileStream >> m_json_config;
    } catch (const JSON::parse_error &e) {
        throw error::InvalidConfig(filePathStr, e.what());
    }
}

void Config::write_derived() const {
    /* Write the json structure to the file */
    std::ofstream ofs{get_file().string()};
    if (ofs.is_open()) {
        ofs << m_json_config.dump(config::json::INDENT);
    } else {
        throw std::runtime_error{"Unable to open file '" + get_file().string() +
                                 "'"};
    }
}

void Config::initialise_file_derived() const {
    /* Create an empty json structure */
    JSON j_file(JSON::value_t::object);

    /* Write the json structure to the file */
    std::ofstream ofs{get_file().string()};
    if (ofs.is_open()) {
        ofs << j_file.dump(config::json::INDENT);
    } else {
        throw std::runtime_error{"Unable to open file '" + get_file().string() +
                                 "'"};
    }
}

} // namespace file
} // namespace todo
