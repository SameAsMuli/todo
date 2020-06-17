#include <filesystem> // std::filesystem

#include "InputParser.hpp"
#include "TodoFunctionAbstract.hpp"

#ifndef ADD_FUNCTION_H
#define ADD_FUNCTION_H

namespace fs = std::filesystem;

class AddFunction : public TodoFunctionAbstract {

    public:
        AddFunction(fs::path todoFile, InputParser& input);

        void run() override;

    private:
        InputParser mInput;
        fs::path    mTodoFile;
};

#endif
