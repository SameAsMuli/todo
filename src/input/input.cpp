#include <algorithm> // std::find
#include <stdexcept> // std::logic_error

#include "SafeInt.hpp"

#include "input/input.hpp"

namespace input {

Input::Input(int argc, char const *const *argv) {
    if (argv == NULL) {
        throw std::logic_error{"NULL passed to Input constructor"};
    }

    if (argc < 1) {
        throw std::logic_error{
            "Invalid argc value passed to Input constructor"};
    }

    for (int i = 1; i < argc; ++i) {
        this->m_tokens.push_back(std::string(argv[i]));
    }
}

const std::vector<std::string>::size_type Input::ACTION_INDEX = 0;

const std::vector<std::string>::size_type Input::PARAM_START_INDEX = 1;

std::vector<std::string>::size_type Input::size() const {
    return this->m_tokens.size();
}

bool Input::isEmpty() const { return this->m_tokens.empty(); }

bool Input::hasOption(const std::string &option) const {
    if (option.empty()) {
        return false;
    }

    return std::find(this->m_tokens.begin(), this->m_tokens.end(), option) !=
           this->m_tokens.end();
}

bool Input::hasOption(int index) const {
    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        return false;
    }

    return this->m_tokens.size() > safeIndex;
}

bool Input::hasOption(const std::string &option, int index) const {
    if (option.empty()) {
        return false;
    }

    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        return false;
    }

    return this->getOption(safeIndex) == option;
}

std::string Input::getOption(int index) const {
    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        throw std::runtime_error{"Invalid index passed to Input::getOption"};
    }

    return this->m_tokens.at(safeIndex);
}

std::string Input::toString(int index) const {
    std::vector<std::string>::size_type safeIndex;
    if (!SafeCast(index, safeIndex)) {
        throw std::runtime_error{"Invalid index passed to Input::toString"};
    }

    std::string str;
    for (auto i = safeIndex; i < this->m_tokens.size(); i++) {
        if (!str.empty()) {
            str += " ";
        }
        str += this->m_tokens[i];
    }
    return str;
}

} // namespace input
