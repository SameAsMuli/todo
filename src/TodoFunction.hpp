#include <string>     // std::string

#ifndef TODO_FUNCTION_H
#define TODO_FUNCTION_H

class TodoFunction {

    public:
        TodoFunction(const std::string& name,
                const std::string& helpText);

        std::string getName()     { return mName;     }
        std::string getHelpText() { return mHelpText; }

        virtual void run() = 0;

    private:
        std::string mName;
        std::string mHelpText;
};

#endif
