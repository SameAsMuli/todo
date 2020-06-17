#include <vector> // std::vector

#include "InputParser.hpp"
#include "TodoFunctionAbstract.hpp"

#ifndef HELP_FUNCTION_H
#define HELP_FUNCTION_H

class HelpFunction : public TodoFunctionAbstract {

    public:
        HelpFunction();

        void addFunctions(std::vector<TodoFunctionAbstract*>& functions);

        void run() override;

    private:
        std::vector<TodoFunctionAbstract*> m_functions;

        static bool todoFuncComp(
                TodoFunctionAbstract* tf1,
                TodoFunctionAbstract* tf2 );
};

#endif
