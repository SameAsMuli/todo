#include <stdexcept> // std::runtime_error

#ifndef TODO_INSPECIFIC_TASK_H
#define TODO_INSPECIFIC_TASK_H

namespace todo {

class InspecificTask : public std::runtime_error {

    public:
        InspecificTask(unsigned int count);
};

} // namespace todo

#endif
