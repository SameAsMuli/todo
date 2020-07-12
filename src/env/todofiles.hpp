#include <filesystem> // std::filesystem

namespace fs = std::filesystem;

#ifndef TODO_FILES_H
#define TODO_FILES_H

class TodoFiles {

    public:
        static void initialise();

        static fs::path getArchive();
        static fs::path getLow();
        static fs::path getNormal();
        static fs::path getUrgent();

    private:
        static void initialiseFile(const fs::path& file);
};

#endif