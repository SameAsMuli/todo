#include <algorithm> // std::find
#include <stdexcept> // std::logic_error

#include "SafeInt.hpp"

#include "input/input.hpp"

namespace {

const std::vector<std::string>::size_type ACTION_INDEX = 1;

const std::vector<std::string>::size_type PARAM_START_INDEX = 2;

bool hasPrefix(const std::string &str, const std::string &prefix) {
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
            "Invalid argc value passed to Input constructor"};
    }

    bool processOptions = true;

    for (int i = ACTION_INDEX; i < argc; ++i) {
        auto arg = std::string(argv[i]);

        if (processOptions) {
            if (arg == Option::LONG_OPTION_PREFIX) {
                processOptions = false;
                continue;
            }

            if (hasPrefix(arg, Option::LONG_OPTION_PREFIX)) {
                /* Remove the prefix and convert to an option */
                auto option =
                    Option(arg.erase(0, Option::LONG_OPTION_PREFIX.size()));

                if (option == input::Option::UNKNOWN_OPTION) {
                    throw std::runtime_error("Unknown option '" + arg + "'");
                }

                std::vector<std::string> optionArgs;

                for (int j = 1; j <= option.getParamCount(); j++) {
                    optionArgs.push_back(argv[++i]);
                }

                this->m_options.insert_or_assign(option, optionArgs);
                continue;

            } else if (hasPrefix(arg, Option::SHORT_OPTION_PREFIX)) {
                /* Remove the prefix and convert to an option */
                arg.erase(0, Option::SHORT_OPTION_PREFIX.size());

                /* Handle multiple short options e.g. -al */
                for (std::string::size_type j = 0; j < arg.size(); ++j) {
                    auto option = Option(arg[j]);
                    if (option == input::Option::UNKNOWN_OPTION) {
                        throw std::runtime_error("Unknown option '" + arg +
                                                 "'");
                    }

                    std::vector<std::string> optionArgs;

                    if (option.getParamCount() > 0) {
                        if (j < arg.size() - 1) {
                            throw std::runtime_error(
                                "No parameters given to option '" +
                                option.toString() + "'");
                        }

                        for (int j = 1; j <= option.getParamCount(); j++) {
                            optionArgs.push_back(argv[++i]);
                        }
                    }

                    this->m_options.insert_or_assign(option, optionArgs);
                }

                continue;
            }

            if (m_action.empty()) {
                m_action = arg;
                continue;
            }

            /* Once we have stopped receiving valid options and the action has
             * been specified, assume the user is passing normal aguments.
             */
            processOptions = false;
        }

        if (m_action.empty()) {
            m_action = arg;
            continue;
        }

        this->m_actionArgs.push_back(arg);
    }
}

unsigned int Input::getActionArgCount() const {
    return this->m_actionArgs.size();
}

std::string Input::getActionArg(int index) const {
    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        throw std::runtime_error{"Invalid index passed to Input::getActionArg"};
    }

    return this->m_actionArgs.at(safeIndex);
}

std::string Input::getActionArgString(int index) const {
    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        throw std::runtime_error{
            "Invalid index passed to Input::getActionArgString"};
    }

    std::string str;
    for (auto i = safeIndex; i < this->m_actionArgs.size(); i++) {
        if (!str.empty()) {
            str += " ";
        }
        str += this->m_actionArgs[i];
    }
    return str;
}

bool Input::hasActionArg(int index) const {
    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        return false;
    }

    return this->m_actionArgs.size() > safeIndex;
}

bool Input::hasActionArg(const std::string &arg) const {
    if (arg.empty()) {
        return false;
    }

    return std::find(this->m_actionArgs.begin(), this->m_actionArgs.end(),
                     arg) != this->m_actionArgs.end();
}

bool Input::hasActionArg(const std::string &arg, int index) const {
    if (arg.empty()) {
        return false;
    }

    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        return false;
    }

    return this->getActionArg(safeIndex) == arg;
}

bool Input::hasOption(const Option &option) const {
    return this->m_options.count(option);
}

std::unordered_set<Option> Input::getOptions() const {
    std::unordered_set<Option> options;
    for (auto const &o : m_options) {
        options.insert(o.first);
    }
    return options;
}

std::vector<std::string> Input::getOptionArgs(const Option &option) const {
    auto args = this->m_options.find(option);
    if (args == this->m_options.end()) {
        return {};
    }
    return args->second;
}

} // namespace input
