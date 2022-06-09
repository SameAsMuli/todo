#include "action/high.hpp"
#include "task/high.hpp"

namespace todo {
namespace action {

High::High()
    : AddOutstandingAbstract("high", "Add a high priority TODO",
                             new task::High{}) {}

} // namespace action
} // namespace todo
