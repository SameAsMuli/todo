#include <filesystem> // std::filesystem

namespace fs = std::filesystem;

#ifndef TODO_FILES_H
#define TODO_FILES_H

class TodoFiles {

    public:
        TodoFiles();

        fs::path getArchive() const { return m_archive; }
        fs::path getLow()     const { return m_low;     }
        fs::path getNormal()  const { return m_normal;  }
        fs::path getUrgent()  const { return m_urgent;  }

    private:
        fs::path m_archive;
        fs::path m_low;
        fs::path m_normal;
        fs::path m_urgent;

        static void initialiseFile(const fs::path& file);
};

#endif
