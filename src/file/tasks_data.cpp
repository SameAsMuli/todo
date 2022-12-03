#include <chrono>  // std::chrono
#include <fstream> // std::ifstream, std::ofstream

#include "config/json.hpp"
#include "error/invalid_config.hpp"
#include "file/definitions.hpp"
#include "file/tasks_data.hpp"
#include "task/task.hpp"
#include "task/type.hpp"

namespace {

static const std::string KEY_DESCRIPTION = "description";
static const std::string KEY_PREV_TIME_ADDED = "previousTimeAdded";
static const std::string KEY_PREV_TYPE = "previousType";
static const std::string KEY_TASKS = "tasks";
static const std::string KEY_TIME_ADDED = "timeAdded";
static const std::string KEY_TYPE = "type";

std::string get_string_from_json(const std::string &filePath, const JSON &json,
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

time_t get_time_t_from_json(const std::string &filePath, const JSON &json,
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

TasksData::TasksData(const File &fileType, const std::filesystem::path &dir)
    : FileAbstract(fileType, dir, "data") {
    switch (fileType) {
    case File::archived_tasks:
    case File::tasks:
        break;
    default:
        throw std::logic_error{"file type '" + fileType.file_name() +
                               "' is not a tasks file"};
    }
    read();
}

void TasksData::add_task(const task::Task &task) { m_tasks.push_back(task); }

unsigned int
TasksData::remove_tasks(std::function<bool(const task::Task &)> matchFunc) {
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

    for (const auto &task : m_tasks) {
        if (searchFunc(task)) {
            matchingTasks.push_back(task);
        }
    }

    return matchingTasks;
}

void TasksData::for_each(std::function<void(task::Task &)> function) {
    for (auto &task : m_tasks) {
        function(task);
    }
}

void TasksData::for_each(
    std::function<void(const task::Task &)> function) const {
    for (const auto &task : m_tasks) {
        function(task);
    }
}

void TasksData::read_derived() {
    auto filePathStr = get_file().string();

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

    std::vector<task::Task> tasks;

    for (const auto &j_task : j_tasks) {
        task::Task task;

        task.set_type(
            task::Type{get_string_from_json(filePathStr, j_task, KEY_TYPE)});
        task.set_previous_type(task::Type{
            get_string_from_json(filePathStr, j_task, KEY_PREV_TYPE)});
        task.set_description(
            get_string_from_json(filePathStr, j_task, KEY_DESCRIPTION));

        auto t = std::chrono::system_clock::from_time_t(
            get_time_t_from_json(filePathStr, j_task, KEY_TIME_ADDED));
        task.set_time_added(t);

        t = std::chrono::system_clock::from_time_t(
            get_time_t_from_json(filePathStr, j_task, KEY_PREV_TIME_ADDED));
        task.set_previous_time_added(t);

        tasks.push_back(task);
    }

    m_tasks = tasks;
}

void TasksData::write_derived() const {
    JSON j_taskFile;

    std::vector<JSON> j_tasks;

    /* Populate a json array with task data */
    for (const auto &task : m_tasks) {
        JSON j_task;

        j_task[KEY_TYPE] = task.get_type().to_string();
        j_task[KEY_PREV_TYPE] = task.get_previous_type().to_string();
        j_task[KEY_DESCRIPTION] = task.get_description();
        j_task[KEY_TIME_ADDED] =
            std::chrono::system_clock::to_time_t(task.get_time_added());
        j_task[KEY_PREV_TIME_ADDED] = std::chrono::system_clock::to_time_t(
            task.get_previous_time_added());

        j_tasks.push_back(j_task);
    }

    /* Add the array to the main json structure */
    j_taskFile[KEY_TASKS] = j_tasks;

    /* Write the json structure to the tasks file */
    std::ofstream ofs{get_file().string()};
    if (ofs.is_open()) {
        ofs << j_taskFile.dump(config::json::INDENT);
    } else {
        throw std::runtime_error{"Unable to open file '" + get_file().string() +
                                 "'"};
    }
}

void TasksData::initialise_file_derived() const {
    /* Add an empty array of tasks to a json structure */
    JSON j_taskFile;
    j_taskFile[KEY_TASKS] = JSON::array({});

    /* Write the json structure to the tasks file */
    std::ofstream ofs{get_file().string()};
    if (ofs.is_open()) {
        ofs << j_taskFile.dump(config::json::INDENT);
    } else {
        throw std::runtime_error{"Unable to open file '" + get_file().string() +
                                 "'"};
    }
}

} // namespace file
} // namespace todo
