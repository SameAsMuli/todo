#include <vector> // std::vector

#include "TodoFunction.hpp"

#ifndef HELP_FUNCTION_H
#define HELP_FUNCTION_H

class HelpFunction : public TodoFunction {

    public:
        HelpFunction();

        void addFunction(TodoFunction* func);

        void run() override;

    private:
        std::vector<TodoFunction*> funcs;
};

#endif
