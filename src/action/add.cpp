#include "action/add.hpp"
#include "task/normal.hpp"

namespace todo {
namespace action {

Add::Add()
    : AddOutstandingAbstract("add", "Add a normal priority TODO",
                             new task::Normal{}) {
    this->addAlias("normal");
}

} // namespace action
} // namespace todo
