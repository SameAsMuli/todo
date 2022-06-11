#include <sstream> // std::stringstream

#include "task/rejected.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Rejected::Rejected() : CompleteAbstract("rejected", '/') {}

} // namespace task
} // namespace todo
