#include <chrono>    // std::chrono
#include <cstdio>    // std::perror, std::remove, std::rename
#include <fstream>   // std::ifstream, std::ofstream
#include <stdexcept> // std::runtime_error

#include "task/complete_abstract.hpp"
#include "task/metadata.hpp"
#include "task/task.hpp"
#include "todo/files.hpp"
#include "todo/inspecific_task.hpp"
#include "todo/unknown_task.hpp"

namespace task {

CompleteAbstract::CompleteAbstract(Prefix prefix)
    : TaskTypeAbstract(todo::files::getComplete(), prefix) {}

void CompleteAbstract::add(const util::Input &input) {
    /* Form the seach string */
    auto searchString = input.toString(util::Input::PARAM_START_INDEX);
    if (searchString.empty()) {
        throw std::logic_error{"Empty input passed to add method"};
    }

    /* Open both the outstanding file and a temp file */
    std::ifstream ifs{todo::files::getOutstanding().string()};
    if (!ifs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    std::ofstream temp{todo::files::getTemp().string()};
    if (!temp.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Attempt to find tasks that match the search string */
    Task task;
    Task match;
    unsigned int count = 0;
    while (ifs >> task) {
        if (task.getDescription().find(searchString) != std::string::npos) {
            match = task;
            count++;
        } else if (count <= 1) {
            /* Write any task that doesn't match into the temp file */
            temp << task << '\n';
        }
    }

    ifs.close();
    temp.close();

    /* Error if no tasks, or more than one task, matched the search string */
    if (count == 0) {
        std::remove(todo::files::getTemp().string().c_str());
        throw todo::UnknownTask();
    } else if (count > 1) {
        std::remove(todo::files::getTemp().string().c_str());
        throw todo::InspecificTask(count);
    }

    /* Update the found task with the current time and the previous prefix */
    Metadata metadata;
    metadata.setTimeAdded(std::chrono::system_clock::now());
    metadata.setPreviousPrefix(match.getPrefix());

    match.setPrefix(this->getPrefix());
    match.setMetadata(metadata);

    /* Write the task to the complete file */
    std::ofstream ofs{this->getFile().string(), std::ios_base::app};
    if (ofs.is_open()) {
        ofs << match << std::endl;
    } else {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    /* Overwrite outstanding file with temp file (removes the matched task) */
    if (std::remove(todo::files::getOutstanding().string().c_str()) ||
        std::rename(todo::files::getTemp().string().c_str(),
                    todo::files::getOutstanding().string().c_str())) {
        std::perror("Error swapping files");
        throw std::runtime_error{"Unable to update TODO file"};
    }
}

} // namespace task
