#include <vector> // std::vector

#include "InputParser.hpp"
#include "TodoFunction.hpp"

#ifndef HELP_FUNCTION_H
#define HELP_FUNCTION_H

class HelpFunction : public TodoFunction {

    public:
        HelpFunction();

        void addFunctions(std::vector<TodoFunction*>& functions);

        void run() override;

    private:
        std::vector<TodoFunction*> funcs;
};

#endif
