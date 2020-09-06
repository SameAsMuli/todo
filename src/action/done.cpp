#include "action/done.hpp"
#include "task/done.hpp"

namespace action {

Done::Done(const util::Input& input):
    AddAbstract( "done", "Mark a TODO as finished", input, new task::Done{})
{ }

} // namespace action
