#include <algorithm> // std::find

#include "util/input.hpp"

namespace util {

Input::Input(int argc, char const* const * argv)
{
    for (int i = 1; i < argc; ++i) {
        this->m_tokens.push_back(std::string(argv[i]));
    }
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

} // namespace util
