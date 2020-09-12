#include <cstdio>  // std::perror, std::remove, std::rename
#include <fstream> // std::ofstream

#include "todo/files.hpp"
#include "task/complete_abstract.hpp"
#include "todo/inspecific_task.hpp"
#include "todo/unknown_task.hpp"

namespace task {

CompleteAbstract::CompleteAbstract(char prefix):
    TaskTypeAbstract(todo::files::getComplete(), prefix)
{ }

void CompleteAbstract::add(const util::Input& input)
{
    auto searchString = input.toString(util::Input::PARAM_START_INDEX);
    if (searchString.empty()) {
        throw std::logic_error{"Empty input passed to add method"};
    }

    std::ifstream ifs{todo::files::getOutstanding().string()};
    if (!ifs.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    std::ofstream temp{todo::files::getTemp().string()};
    if (!temp.is_open()) {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    Task task;
    Task match;
    unsigned int count = 0;
    while (ifs >> task) {
       if (task.getDescription().find(searchString) != std::string::npos) {
           match = task;
           count++;
       } else if (count <= 1) {
           temp << task;
       }
    }

    ifs.close();
    temp.close();

    if (count == 0) {
        std::remove(todo::files::getTemp().string().c_str());
        throw todo::UnknownTask();
    } else if (count > 1) {
        std::remove(todo::files::getTemp().string().c_str());
        throw todo::InspecificTask(count);
    }

    std::ofstream ofs{this->getFile().string(), std::ios_base::app};
    if (ofs.is_open()) {
        ofs << this->getPrefix() << " " << match.getDescription() << std::endl;
    } else {
        throw std::runtime_error{"Unable to open TODO file"};
    }

    if (std::remove(todo::files::getOutstanding().string().c_str()) ||
        std::rename(todo::files::getTemp().string().c_str(),
                    todo::files::getOutstanding().string().c_str())) {
        std::perror("Error swapping files");
        throw std::runtime_error{"Unable to update TODO file"};
    }
}

} // namespace task
