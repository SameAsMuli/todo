#include <algorithm> // std::find

#include "InputParser.hpp"

InputParser::InputParser(int argc, char const* const * argv)
{
    for (int i = 1; i < argc; ++i) {
        this->tokens.push_back(std::string(argv[i]));
    }
}

bool InputParser::isEmpty() const
{
    return this->tokens.empty();
}

bool InputParser::hasOption(const std::string& option) const
{
    return std::find(this->tokens.begin(), this->tokens.end(), option)
        != this->tokens.end();
}

bool InputParser::hasOption(const std::string& option,
        std::vector<std::string>::size_type index) const
{
    return this->tokens.at(index) == option;
}

std::string InputParser::getOption(
        std::vector<std::string>::size_type index) const
{
    return this->tokens.at(index);
}
