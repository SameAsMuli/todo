#include <algorithm> // std::find

#include "util/inputparser.hpp"

InputParser::InputParser(int argc, char const* const * argv)
{
    for (int i = 1; i < argc; ++i) {
        this->m_tokens.push_back(std::string(argv[i]));
    }
}

bool InputParser::isEmpty() const
{
    return this->m_tokens.empty();
}

bool InputParser::hasOption(const std::string& option) const
{
    return std::find(this->m_tokens.begin(), this->m_tokens.end(), option)
        != this->m_tokens.end();
}

bool InputParser::hasOption(
        std::vector<std::string>::size_type index) const
{
    return this->m_tokens.size() > index;
}

bool InputParser::hasOption(const std::string& option,
        std::vector<std::string>::size_type index) const
{
    return this->m_tokens.at(index) == option;
}

std::string InputParser::getOption(
        std::vector<std::string>::size_type index) const
{
    return this->m_tokens.at(index);
}
