#include <chrono> // std::chrono

#include "file/definitions.hpp"
#include "file/mutators.hpp"
#include "file/tasks_data.hpp"

namespace todo {
namespace file {

void archive_tasks(unsigned int maxMins, bool global) {
    auto archiveTasks = TasksData{File::archived_tasks, global};
    auto now = std::chrono::system_clock::now();
    auto tasks = TasksData{File::tasks, global};

    tasks.remove_tasks([&archiveTasks, maxMins, now](auto &task) {
        if (!task.get_type().is_complete())
            return false;

        auto ageMins = std::chrono::duration_cast<std::chrono::minutes>(
                           now - task.get_time_added())
                           .count();

        if (maxMins <= ageMins) {
            archiveTasks.add_task(task);
            return true;
        }
        return false;
    });

    archiveTasks.write();
    tasks.write();
}

} // namespace file
} // namespace todo
