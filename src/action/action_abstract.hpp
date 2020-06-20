#include <string> // std::string

#ifndef ACTION_ABSTRACT_H
#define ACTION_ABSTRACT_H

namespace action {

class ActionAbstract {

    public:
        ActionAbstract(
                const std::string& name,
                const std::string& helpText);

        std::string getName()     { return m_name;     }
        std::string getHelpText() { return m_helpText; }

        virtual void run() = 0;

    private:
        std::string m_name;
        std::string m_helpText;
};

} // namespace action

#endif
