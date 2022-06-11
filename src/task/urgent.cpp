#include <sstream> // std::stringstream

#include "task/urgent.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Urgent::Urgent() : OutstandingAbstract("urgent", '#') {}

} // namespace task
} // namespace todo
