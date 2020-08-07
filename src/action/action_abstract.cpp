#include "action/action_abstract.hpp"

namespace action {

ActionAbstract::ActionAbstract(
        const std::string& name,
        const std::string& helpText,
        const util::InputParser& input):
    m_name(name),
    m_helpText(helpText),
    m_input(input)
{ }

} // namespace action
