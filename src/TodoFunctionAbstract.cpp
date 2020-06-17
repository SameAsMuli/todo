#include "TodoFunctionAbstract.hpp"

TodoFunctionAbstract::TodoFunctionAbstract(const std::string& name,
        const std::string& helpText)
{
    this->mName = name;
    this->mHelpText = helpText;
}

