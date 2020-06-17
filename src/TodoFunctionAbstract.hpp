#include <string> // std::string

#ifndef TODO_FUNCTION_H
#define TODO_FUNCTION_H

class TodoFunctionAbstract {

    public:
        TodoFunctionAbstract(
                const std::string& name,
                const std::string& helpText);

        std::string getName()     { return m_name;     }
        std::string getHelpText() { return m_helpText; }

        virtual void run() = 0;

    private:
        std::string m_name;
        std::string m_helpText;
};

#endif
