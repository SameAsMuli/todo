#include <iostream> // std::cout
#include <utility>  // std::pair

#include "action/help.hpp"
#include "error/unknown_argument.hpp"
#include "file/definitions.hpp"
#include "input/option.hpp"
#include "util/display.hpp"
#include "util/string.hpp"

namespace todo {
namespace action {

Help::Help() : ActionAbstract("help", "Display this help text", 1) {}

std::string Help::description() const {
    return "If run with no arguments, then general information about the "
           "program will be shown. If passed an action as an argument, then "
           "detailed information on that specific action will be shown.";
}

std::string Help::usage() const {
    return "usage: todo " + this->get_name() + " [<action>]";
}

void Help::add_actions(std::vector<ActionAbstract *> &actions) {
    this->m_actions = actions;
}

/*** PRIVATE METHODS ***/

void Help::run(const input::Input &input) {
    if (!input.has_action_arg(0)) {
        std::vector<std::pair<std::string, std::string>> actions;

        std::transform(this->m_actions.begin(), this->m_actions.end(),
                       std::back_inserter(actions), [](const auto &action) {
                           return std::make_pair(action->get_name(),
                                                 action->get_help_text());
                       });

        std::cout << util::display::program_overview(actions) << std::endl;
    } else {
        auto actionName = input.get_action_arg(0);
        auto action =
            std::find_if(this->m_actions.begin(), this->m_actions.end(),
                         [&actionName](const auto &action) {
                             return action->get_name() == actionName;
                         });

        if (action == this->m_actions.end())
            throw error::UnknownArgument(actionName, "action");

        (*action)->print_details();
    }
}

} // namespace action
} // namespace todo
