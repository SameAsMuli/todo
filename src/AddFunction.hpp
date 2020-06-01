#include "InputParser.hpp"
#include "TodoFunction.hpp"

#ifndef ADD_FUNCTION_H
#define ADD_FUNCTION_H

class AddFunction : public TodoFunction {

    public:
        AddFunction(InputParser& ip);

        void run() override;

    private:
        InputParser input;
};

#endif
