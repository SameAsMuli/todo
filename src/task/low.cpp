#include <sstream> // std::stringstream

#include "task/low.hpp"
#include "util/ansi.hpp"

namespace todo {
namespace task {

Low::Low() : OutstandingAbstract("low", '~') {}

} // namespace task
} // namespace todo
