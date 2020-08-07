#include <string> // std::string

#include "util/inputparser.hpp"

#ifndef ACTION_ABSTRACT_H
#define ACTION_ABSTRACT_H

namespace action {

class ActionAbstract {

    public:
        ActionAbstract(
                const std::string& name,
                const std::string& helpText,
                const util::InputParser& input);

        std::string getName() { return m_name; }
        std::string getHelpText() { return m_helpText; }
        util::InputParser getInput() { return m_input; }

        virtual void run() = 0;

    private:
        std::string m_name;
        std::string m_helpText;
        util::InputParser m_input;
};

} // namespace action

#endif
