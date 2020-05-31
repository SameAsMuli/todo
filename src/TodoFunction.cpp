#include "TodoFunction.hpp"

TodoFunction::TodoFunction(const std::string& name,
        const std::string& helpText,
        const std::function<void(int argc, char** argv)>& func)
{
    this->mName = name;
    this->mHelpText = helpText;
    this->mFunc = func;
}

