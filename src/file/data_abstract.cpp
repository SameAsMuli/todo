#include "file/data_abstract.hpp"
#include "file/tasks_data.hpp"
#include "util/fs.hpp"

namespace todo {
namespace file {

DataAbstract::DataAbstract(File fileType, bool global)
    : m_fileType(fileType), m_global(global) {}

DataAbstract *DataAbstract::init(File fileType, bool global) {
    switch (fileType) {
    case File::archived_tasks:
    case File::tasks:
        return new TasksData{fileType, global};
    }
}

std::filesystem::path DataAbstract::get_file() const {
    return get_todo_dir(m_global) / "data" / m_fileType.file_name();
}

void DataAbstract::read() {
    /* Ensure the file and directory exist before reading */
    initialise_file();
    read_derived();
}

void DataAbstract::write() const {
    /* Ensure the file and directory exist before writing */
    initialise_file();
    write_derived();
}

void DataAbstract::initialise_file() const {
    /* Create the file and directory if it doesn't already exist */
    util::fs::init_file(get_file());

    /* Allow derived classes to perform any extra initialisation they need */
    initialise_file_derived();
}

} // namespace file
} // namespace todo
