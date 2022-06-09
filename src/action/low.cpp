#include "action/low.hpp"
#include "task/low.hpp"

namespace todo {
namespace action {

Low::Low()
    : AddOutstandingAbstract("low", "Add a low priority TODO",
                             new task::Low{}) {}

} // namespace action
} // namespace todo
