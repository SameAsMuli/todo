#include "action/high.hpp"
#include "task/high.hpp"

namespace todo {
namespace action {

High::High(const input::Input &input)
    : AddAbstract("high", "Add a high priority TODO", input, new task::High{}) {
}

} // namespace action
} // namespace todo
