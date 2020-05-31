#include <functional> // std::function
#include <string>     // std::string

#ifndef TODO_FUNCTION_H
#define TODO_FUNCTION_H

class TodoFunction {

    public:
        TodoFunction(const std::string name,
                const std::string helpText,
                const std::function<void(int argc, char** argv)> func);


        std::string getName()                                { return mName;     }
        std::string getHelpText()                            { return mHelpText; }
        std::function<void(int argc, char** argv)> getFunc() { return mFunc;     }

    private:
        std::string mName;
        std::string mHelpText;
        std::function<void(int argc, char** argv)> mFunc;
};

#endif
