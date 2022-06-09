#include "action/done.hpp"
#include "task/done.hpp"

namespace todo {
namespace action {

Done::Done()
    : AddCompleteAbstract("done", "Mark a TODO as finished", new task::Done{}) {
}

} // namespace action
} // namespace todo
