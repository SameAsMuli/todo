#include <filesystem> // std::filesystem

#include "task/task.hpp"
#include "util/input.hpp"

#ifndef TASK_TASK_TYPE_ABSTRACT_H
#define TASK_TASK_TYPE_ABSTRACT_H

namespace task {

class TaskTypeAbstract {

    public:
        TaskTypeAbstract(const std::filesystem::path& file, char prefix);

        std::filesystem::path getFile() const { return m_file; }

        char getPrefix() const { return m_prefix; }

        void view();

        virtual void add(const util::Input& input) = 0;

    private:
        const std::filesystem::path m_file;

        const char m_prefix;

        virtual std::string format(const Task& task) = 0;
};

} // namespace task

#endif
