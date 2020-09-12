#include <fstream> // std::ofstream
#include <string>  // std::string

#include "todo/files.hpp"
#include "util/fs.hpp"
#include "util/xdg.hpp"

namespace {

void initialiseFile(const fs::path& file)
{
    // Create parent directory if it doesn't already exist
    fs::create_directories(file.parent_path());

    // Create file if it doesn't already exist
    if (!fs::exists(file)) {
        std::ofstream(file.string()); // create file
    }
}

} // namespace

namespace todo {
namespace files {

void initialise()
{
    if (util::fs::HomeDir().empty()) {
        throw std::runtime_error("Unable to find HOME directory.");
    }

    initialiseFile(getOutstanding());
    initialiseFile(getComplete());
}

fs::path getOutstanding()
{
    return getTodoDir() / "outstanding_tasks";
}

fs::path getComplete()
{
    return getTodoDir() / "complete_tasks";
}

fs::path getTemp()
{
    return getTodoDir() / "temp";
}

fs::path getTodoDir()
{
    return util::xdg::configHome() / "todo";
}

} // namespace files
} // namespace todo
