#include "action/config.hpp"
#include "config/config.hpp"
#include "error/empty_argument.hpp"
#include "util/string.hpp"

namespace todo {
namespace action {

Config::Config()
    : ActionAbstract("config", "Query and modify program configuration") {
    this->add_valid_option(input::Option::global);
}

std::string Config::description() const {
    return "Query and modify the program configuration files. If given no "
           "arguments, the current configuration will be printed to the "
           "terminal. If given a key and value, the configuration will be "
           "updated. If given a key and no value, the configuration will be "
           "queried.";
}

std::string Config::usage() const {
    return "usage: todo " + this->get_name() + " <key>[=<value>]";
}

void Config::run(const input::Input &input) {
    auto global = input.has_option(input::Option::global);

    if (input.get_action_arg_count() == 0) {
        for (const config::Key &key : config::Key::ALL_KEYS) {
            std::cout << key.to_string() << " = "
                      << config::Config::get_str(key, global) << std::endl;
        }
    }

    for (const auto &arg : input.get_action_args()) {
        auto pos = arg.find("=");

        if (pos == std::string::npos) {
            /* Print the config value */
            auto value = config::Config::get_str(ConfigKey{arg}, global);
            if (!value.empty())
                std::cout << value << std::endl;
        } else {
            /* Set the config value */
            ConfigKey key{util::string::trim_copy(arg.substr(0, pos))};
            auto field =
                util::string::trim_copy(arg.substr(pos + 1, std::string::npos));
            config::Config::set_str(key, field, global);
        }
    }
}

} // namespace action
} // namespace todo
