#include <chrono> // std::chrono

#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "file/tasks_data.hpp"

namespace todo {
namespace file {

void archiveTasks(unsigned int maxMins, bool global) {
    auto archiveTasks = TasksData{File::archived_tasks, global};
    auto now = std::chrono::system_clock::now();
    auto tasks = TasksData{File::tasks, global};

    tasks.removeTasks([&archiveTasks, maxMins, now](auto &task) {
        if (!task.getType().isComplete())
            return false;

        auto ageMins = std::chrono::duration_cast<std::chrono::minutes>(
                           now - task.getTimeAdded())
                           .count();

        if (maxMins <= ageMins) {
            archiveTasks.addTask(task);
            return true;
        }
        return false;
    });

    archiveTasks.write();
    tasks.write();
}

} // namespace file
} // namespace todo
