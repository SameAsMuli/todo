#include <algorithm> // std::find
#include <stdexcept> // std::logic_error

#include "input/input.hpp"

namespace {

const std::vector<std::string>::size_type ACTION_INDEX = 1;

const std::vector<std::string>::size_type PARAM_START_INDEX = 2;

bool has_prefix(const std::string &str, const std::string &prefix) {
    return prefix.size() < str.size() &&
           std::mismatch(prefix.begin(), prefix.end(), str.begin()).first ==
               prefix.end();
}

} // namespace

namespace input {

Input::Input(int argc, char const *const *argv) {
    if (argv == NULL) {
        throw std::logic_error{"NULL passed to Input constructor"};
    }

    if (argc < 1) {
        throw std::logic_error{
            "invalid argc value passed to Input constructor"};
    }

    bool processOptions = true;

    for (int i = ACTION_INDEX; i < argc; ++i) {
        auto arg = std::string(argv[i]);

        if (processOptions) {
            if (arg == Option::LONG_OPTION_PREFIX) {
                processOptions = false;
                continue;
            }

            if (has_prefix(arg, Option::LONG_OPTION_PREFIX)) {
                /* Remove the prefix and convert to an option */
                auto option =
                    Option(arg.erase(0, Option::LONG_OPTION_PREFIX.size()));

                if (option == Option::UNKNOWN_OPTION) {
                    throw std::runtime_error("unknown option '" + arg + "'");
                }

                std::vector<std::string> optionArgs;

                if (option.requires_arg()) {
                    if (i >= argc) {
                        throw std::runtime_error(
                            "no argument given to option '" +
                            option.to_string() + "'");
                    }
                    optionArgs.push_back(argv[++i]);
                }

                this->m_options.insert_or_assign(option, optionArgs);
                continue;

            } else if (has_prefix(arg, Option::SHORT_OPTION_PREFIX)) {
                /* Remove the prefix and convert to an option */
                arg.erase(0, Option::SHORT_OPTION_PREFIX.size());

                /* Handle multiple short options e.g. -al */
                for (std::string::size_type j = 0; j < arg.size(); ++j) {
                    auto option = Option(arg[j]);
                    if (option == Option::UNKNOWN_OPTION) {
                        throw std::runtime_error("unknown option '" + arg +
                                                 "'");
                    }

                    std::vector<std::string> optionArgs;

                    if (option.requires_arg()) {
                        if (j < arg.size() - 1 || i >= argc) {
                            throw std::runtime_error(
                                "no argument given to option '" +
                                option.to_string() + "'");
                        }
                        optionArgs.push_back(argv[++i]);
                    }

                    this->m_options.insert_or_assign(option, optionArgs);
                }

                continue;
            }

            if (m_action.empty()) {
                m_action = arg;
                continue;
            }
        }

        if (m_action.empty()) {
            m_action = arg;
            continue;
        }

        this->m_actionArgs.push_back(arg);
    }
}

unsigned int Input::get_actionArgCount() const {
    return this->m_actionArgs.size();
}

std::string Input::get_actionArg(int index) const {
    if (index < 0) {
        throw std::runtime_error{
            "invalid index passed to Input::get_actionArg"};
    }

    return this->m_actionArgs.at(index);
}

std::string Input::get_actionArgString(int index) const {
    if (index < 0) {
        throw std::runtime_error{
            "invalid index passed to Input::get_actionArgString"};
    }

    std::string str;
    for (auto i = index; i < this->m_actionArgs.size(); i++) {
        if (!str.empty()) {
            str += " ";
        }
        str += this->m_actionArgs[i];
    }
    return str;
}

bool Input::has_action_arg(int index) const {
    if (index < 0) {
        return false;
    }

    return this->m_actionArgs.size() > index;
}

bool Input::has_action_arg(const std::string &arg) const {
    if (arg.empty()) {
        return false;
    }

    return std::find(this->m_actionArgs.begin(), this->m_actionArgs.end(),
                     arg) != this->m_actionArgs.end();
}

bool Input::has_action_arg(const std::string &arg, int index) const {
    if (arg.empty()) {
        return false;
    }

    if (index < 0) {
        return false;
    }

    return this->get_actionArg(index) == arg;
}

bool Input::hasOption(const Option &option) const {
    return this->m_options.count(option);
}

std::unordered_set<Option> Input::get_options() const {
    std::unordered_set<Option> options;
    for (auto const &o : m_options) {
        options.insert(o.first);
    }
    return options;
}

std::vector<std::string> Input::get_option_args(const Option &option) const {
    auto args = this->m_options.find(option);
    if (args == this->m_options.end()) {
        return {};
    }
    return args->second;
}

} // namespace input
