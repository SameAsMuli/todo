#include "action/done.hpp"
#include "task/done.hpp"

namespace todo {
namespace action {

Done::Done(const input::Input &input)
    : AddCompleteAbstract("done", "Mark a TODO as finished", input,
                          new task::Done{}) {}

} // namespace action
} // namespace todo
