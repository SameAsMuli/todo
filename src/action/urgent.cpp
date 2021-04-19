#include "action/urgent.hpp"
#include "task/urgent.hpp"

namespace todo {
namespace action {

Urgent::Urgent(const input::Input &input)
    : AddOutstandingAbstract("urgent", "Add an urgent priority TODO", input,
                             new task::Urgent{}) {}

} // namespace action
} // namespace todo
