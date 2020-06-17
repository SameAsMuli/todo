#include "TodoFunctionAbstract.hpp"

TodoFunctionAbstract::TodoFunctionAbstract(
        const std::string& name,
        const std::string& helpText)
{
    this->m_name = name;
    this->m_helpText = helpText;
}

