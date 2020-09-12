#include <filesystem> // std::filesystem

namespace fs = std::filesystem;

#ifndef ENV_TODO_FILES_H
#define ENV_TODO_FILES_H

class TodoFiles {

    public:
        static void initialise();

        static fs::path getOutstanding();
        static fs::path getComplete();
        static fs::path getTemp();

    private:
        static fs::path getTodoDir();
        static void initialiseFile(const fs::path& file);
};

#endif
