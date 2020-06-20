#include "action/action_abstract.hpp"

namespace action {

ActionAbstract::ActionAbstract(
        const std::string& name,
        const std::string& helpText)
{
    this->m_name = name;
    this->m_helpText = helpText;
}

} // namespace action
