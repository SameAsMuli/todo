#include "InputParser.hpp"
#include "TodoFiles.hpp"
#include "TodoFunctionAbstract.hpp"

#ifndef ADD_FUNCTION_H
#define ADD_FUNCTION_H

class AddFunction : public TodoFunctionAbstract {

    public:
        AddFunction(
                const TodoFiles& todoFiles,
                const InputParser& input);

        void run() override;

    private:
        InputParser m_input;
        TodoFiles   m_todoFiles;
};

#endif
