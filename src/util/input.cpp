#include <algorithm> // std::find

#include "util/input.hpp"

namespace util {

Input::Input(int argc, char const* const* argv)
{
    for (int i = 1; i < argc; ++i) {
        this->m_tokens.push_back(std::string(argv[i]));
    }
}

const std::vector<std::string>::size_type Input::ACTION_INDEX = 0;

const std::vector<std::string>::size_type Input::PARAM_START_INDEX = 1;

std::vector<std::string>::size_type Input::size() const
{
    return this->m_tokens.size();
}

bool Input::isEmpty() const
{
    return this->m_tokens.empty();
}

bool Input::hasOption(const std::string& option) const
{
    return std::find(this->m_tokens.begin(), this->m_tokens.end(), option)
        != this->m_tokens.end();
}

bool Input::hasOption(
        std::vector<std::string>::size_type index) const
{
    return this->m_tokens.size() > index;
}

bool Input::hasOption(const std::string& option,
        std::vector<std::string>::size_type index) const
{
    return this->m_tokens.at(index) == option;
}

std::string Input::getOption(
        std::vector<std::string>::size_type index) const
{
    return this->m_tokens.at(index);
}

std::string Input::toString(std::vector<std::string>::size_type index) const
{
    std::string str;
    for (auto i = index; i < this->m_tokens.size(); i++) {
        if (!str.empty()) {
            str += " ";
        }
        str += this->m_tokens[i];
    }
    return str;
}

} // namespace util
