#include <iostream> // std::cout

#include "action/version.hpp"
#include "util/display.hpp"

namespace todo {
namespace action {

Version::Version(input::Input input)
    : ActionAbstract("version", "Display the program version", input, 0) {}

std::string Version::description() const {
    return "Print the version information of the program.";
}

std::string Version::usage() const { return "usage: todo version"; }

/*** PRIVATE METHODS ***/

void Version::run() {
    std::cout << util::display::programVersion() << std::endl;
}

} // namespace action
} // namespace todo
