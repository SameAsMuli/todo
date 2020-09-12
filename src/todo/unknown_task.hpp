#ifndef TODO_UNKNOWN_TASK_H
#define TODO_UNKNOWN_TASK_H

#include <stdexcept> // std::runtime_error

namespace todo {

class UnknownTask : public std::runtime_error {

    public:
        UnknownTask();
};

} // namespace todo

#endif
