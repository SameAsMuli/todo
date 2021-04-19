#include "action/high.hpp"
#include "task/high.hpp"

namespace todo {
namespace action {

High::High(const input::Input &input)
    : AddOutstandingAbstract("high", "Add a high priority TODO", input,
                             new task::High{}) {}

} // namespace action
} // namespace todo
