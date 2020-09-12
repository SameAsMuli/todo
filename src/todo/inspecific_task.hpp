#ifndef TODO_INSPECIFIC_TASK_H
#define TODO_INSPECIFIC_TASK_H

#include <stdexcept> // std::runtime_error

namespace todo {

class InspecificTask : public std::runtime_error {

    public:
        InspecificTask(unsigned int count);
};

} // namespace todo

#endif
