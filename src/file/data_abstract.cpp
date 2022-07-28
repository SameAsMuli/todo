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

std::filesystem::path DataAbstract::getFile() const {
    return getTodoDir(m_global) / "data" / m_fileType.fileName();
}

void DataAbstract::read() {
    /* Ensure the file and directory exist before reading */
    initialiseFile();
    read_derived();
}

void DataAbstract::write() const {
    /* Ensure the file and directory exist before writing */
    initialiseFile();
    write_derived();
}

void DataAbstract::initialiseFile() const {
    /* Create the file and directory if it doesn't already exist */
    util::fs::initFile(getFile());

    /* Allow derived classes to perform any extra initialisation they need */
    initialiseFile_derived();
}

} // namespace file
} // namespace todo
