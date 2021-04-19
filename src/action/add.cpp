#include "action/add.hpp"
#include "task/normal.hpp"

namespace todo {
namespace action {

Add::Add(const input::Input &input)
    : AddOutstandingAbstract("add", "Add a normal priority TODO", input,
                             new task::Normal{}) {
    this->addAlias("normal");
}

} // namespace action
} // namespace todo
