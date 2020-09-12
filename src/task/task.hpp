#ifndef TASK_TASK_H
#define TASK_TASK_H

#include <iostream> // std::istream

namespace task {

class Task {

  public:
    Task();

    char getPrefix() const { return m_prefix; }

    std::string getDescription() const { return m_description; }

    friend std::istream &operator>>(std::istream &stream, Task &task);

    friend std::ostream &operator<<(std::ostream &stream, Task &task);

  private:
    char m_prefix;

    std::string m_description;
};

} // namespace task

#endif
