#include <string> // std::string

#include "util/input.hpp"

#ifndef ACTION_ABSTRACT_H
#define ACTION_ABSTRACT_H

namespace action {

class ActionAbstract {

    public:
        ActionAbstract(
                const std::string& name,
                const std::string& helpText,
                const util::Input& input);

        std::string getName() { return m_name; }
        std::string getHelpText() { return m_helpText; }
        util::Input getInput() { return m_input; }

        virtual void run() = 0;

    private:
        std::string m_name;
        std::string m_helpText;
        util::Input m_input;
};

} // namespace action

#endif
