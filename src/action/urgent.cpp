#include "action/urgent.hpp"
#include "task/urgent.hpp"

namespace todo {
namespace action {

Urgent::Urgent()
    : AddOutstandingAbstract("urgent", "Add an urgent priority TODO",
                             new task::Urgent{}) {}

} // namespace action
} // namespace todo
