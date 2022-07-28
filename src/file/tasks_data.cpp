#include <chrono>  // std::chrono
#include <fstream> // std::ifstream, std::ofstream

#include "nlohmann/json.hpp"

#include "error/invalid_config.hpp"
#include "file/definitions.hpp"
#include "file/tasks_data.hpp"
#include "task/task.hpp"
#include "task/type.hpp"

using JSON = nlohmann::json;

namespace {

static const std::string KEY_DESCRIPTION = "description";
static const std::string KEY_PREV_TIME_ADDED = "previousTimeAdded";
static const std::string KEY_PREV_TYPE = "previousType";
static const std::string KEY_TASKS = "tasks";
static const std::string KEY_TIME_ADDED = "timeAdded";
static const std::string KEY_TYPE = "type";

std::string getStringFromJson(const std::string &filePath, const JSON &json,
                              const std::string &key) {
    if (!json.contains(key)) {
        throw todo::error::InvalidConfig(filePath,
                                         "no '" + key + "' key found");
    }

    auto value = json[key];
    if (value.is_null()) {
        return std::string{};
    }
    if (!value.is_string()) {
        throw todo::error::InvalidConfig(filePath,
                                         "'" + key + "' is not a string");
    }
    return value.get<std::string>();
}

time_t getTimeTFromJson(const std::string &filePath, const JSON &json,
                        const std::string &key) {
    if (!json.contains(key)) {
        throw todo::error::InvalidConfig(filePath,
                                         "no '" + key + "' key found");
    }

    auto value = json[key];
    if (value.is_null()) {
        return 0;
    }
    if (!value.is_number_integer()) {
        throw todo::error::InvalidConfig(filePath,
                                         "'" + key + "' is not an integer");
    }
    return value.get<time_t>();
}

} // namespace

namespace todo {
namespace file {

TasksData::TasksData(File fileType, bool global)
    : DataAbstract(fileType, global) {
    switch (fileType) {
    case File::archived_tasks:
    case File::tasks:
        break;
    default:
        throw std::logic_error{"file type '" + fileType.fileName() +
                               "' is not a tasks file"};
    }
    read();
}

void TasksData::addTask(const task::Task &task) { m_tasks.push_back(task); }

unsigned int
TasksData::removeTasks(std::function<bool(const task::Task &)> matchFunc) {
    unsigned int matches = 0;

    auto it = m_tasks.begin();
    while (it != m_tasks.end()) {
        if (matchFunc(*it)) {
            it = m_tasks.erase(it);
            matches++;
        } else {
            it++;
        }
    }

    return matches;
}

std::vector<task::Task>
TasksData::search(std::function<bool(const task::Task &)> searchFunc) const {
    std::vector<task::Task> matchingTasks;

    for (auto const &task : m_tasks) {
        if (searchFunc(task)) {
            matchingTasks.push_back(task);
        }
    }

    return matchingTasks;
}

void TasksData::forEach(std::function<void(task::Task &)> function) {
    for (auto &task : m_tasks) {
        function(task);
    }
}

void TasksData::read_derived() {
    auto filePathStr = getFile().string();

    std::ifstream fileStream{filePathStr};
    JSON j_taskFile;

    try {
        fileStream >> j_taskFile;
    } catch (const JSON::parse_error &e) {
        throw error::InvalidConfig(filePathStr, e.what());
    }

    if (!j_taskFile.contains(KEY_TASKS)) {
        throw error::InvalidConfig(filePathStr,
                                   "no '" + KEY_TASKS + "' key found");
    }

    auto j_tasks = j_taskFile[KEY_TASKS];

    if (!j_tasks.is_array()) {
        throw error::InvalidConfig(filePathStr,
                                   "'" + KEY_TASKS + "' is not an array");
    }

    for (auto const &j_task : j_tasks) {
        task::Task task;

        task.setType(
            task::Type{getStringFromJson(filePathStr, j_task, KEY_TYPE)});
        task.setPreviousType(
            task::Type{getStringFromJson(filePathStr, j_task, KEY_PREV_TYPE)});
        task.setDescription(
            getStringFromJson(filePathStr, j_task, KEY_DESCRIPTION));

        auto t = std::chrono::system_clock::from_time_t(
            getTimeTFromJson(filePathStr, j_task, KEY_TIME_ADDED));
        task.setTimeAdded(t);

        t = std::chrono::system_clock::from_time_t(
            getTimeTFromJson(filePathStr, j_task, KEY_PREV_TIME_ADDED));
        task.setPreviousTimeAdded(t);

        m_tasks.push_back(task);
    }
}

void TasksData::write_derived() const {
    JSON j_taskFile;

    std::vector<JSON> j_tasks;

    /* Populate a json array with task data */
    for (auto const &task : m_tasks) {
        JSON j_task;

        j_task[KEY_TYPE] = task.getType().toString();
        j_task[KEY_PREV_TYPE] = task.getPreviousType().toString();
        j_task[KEY_DESCRIPTION] = task.getDescription();
        j_task[KEY_TIME_ADDED] =
            std::chrono::system_clock::to_time_t(task.getTimeAdded());
        j_task[KEY_PREV_TIME_ADDED] =
            std::chrono::system_clock::to_time_t(task.getPreviousTimeAdded());

        j_tasks.push_back(j_task);
    }

    /* Add the array to the main json structure */
    j_taskFile[KEY_TASKS] = j_tasks;

    /* Write the json structure to the tasks file */
    std::ofstream ofs{getFile().string()};
    if (ofs.is_open()) {
        ofs << j_taskFile;
    } else {
        throw std::runtime_error{"Unable to open file '" + getFile().string() +
                                 "'"};
    }
}

void TasksData::initialiseFile_derived() const {
    /* If the file is non-empty, no more initialisation is needed */
    if (std::filesystem::file_size(getFile()) != 0) {
        return;
    }

    /* Add an empty array of tasks to a json structure */
    JSON j_taskFile;
    j_taskFile[KEY_TASKS] = JSON::array({});

    /* Write the json structure to the tasks file */
    std::ofstream ofs{getFile().string()};
    if (ofs.is_open()) {
        ofs << j_taskFile;
    } else {
        throw std::runtime_error{"Unable to open file '" + getFile().string() +
                                 "'"};
    }
}

} // namespace file
} // namespace todo
