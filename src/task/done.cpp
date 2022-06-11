#include <sstream> // std::stringstream

#include "task/done.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Done::Done() : CompleteAbstract("done", '+') {}

} // namespace task
} // namespace todo
