#include "file/file_abstract.hpp"
#include "file/config.hpp"
#include "file/tasks_data.hpp"
#include "util/fs.hpp"

namespace todo {
namespace file {

FileAbstract::FileAbstract(const File &fileType,
                           const std::filesystem::path &dir,
                           const std::filesystem::path &sub_dir)
    : m_fileType(fileType), m_dir(dir), m_sub_dir(sub_dir) {}

FileAbstract *FileAbstract::init(const File &fileType,
                                 const std::filesystem::path &dir) {
    switch (fileType) {
    case File::archived_tasks:
    case File::tasks:
        return new TasksData{fileType, dir};
    case File::config:
        return new Config{dir};
    }

    return nullptr;
}

std::filesystem::path FileAbstract::get_file() const {
    if (m_sub_dir.empty())
        return m_dir / m_fileType.file_name();
    else
        return m_dir / m_sub_dir / m_fileType.file_name();
}

void FileAbstract::read() {
    /* Ensure the file and directory exist before reading */
    initialise_file();
    read_derived();
}

void FileAbstract::write() const {
    /* Ensure the file and directory exist before writing */
    initialise_file();
    write_derived();
}

void FileAbstract::initialise_file() const {
    /* If the file exists and is non-empty, no more initialisation is needed */
    if (std::filesystem::exists(get_file()) &&
        std::filesystem::file_size(get_file()) != 0) {
        return;
    }

    /* Create the file and directory if it doesn't already exist */
    util::fs::init_file(get_file());

    /* Allow derived classes to perform any extra initialisation they need */
    initialise_file_derived();
}

} // namespace file
} // namespace todo
