#include <iostream> // std::cout

#include "action/version.hpp"
#include "util/display.hpp"

namespace todo {
namespace action {

Version::Version()
    : ActionAbstract("version", "Display the program version", 0) {}

std::string Version::description() const {
    return "Print the version information of the program.";
}

std::string Version::usage() const { return "usage: todo " + this->get_name(); }

void Version::run(const input::Input &input) {
    std::cout << util::display::program_version() << std::endl;
}

} // namespace action
} // namespace todo
