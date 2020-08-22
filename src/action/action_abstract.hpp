#include <optional> //std::optional
#include <string>   // std::string

#include "util/input.hpp"

#ifndef ACTION_ABSTRACT_H
#define ACTION_ABSTRACT_H

namespace action {

class ActionAbstract {

    public:
        ActionAbstract(
                const std::string& name,
                const std::string& helpText,
                const util::Input& input,
                std::optional<unsigned int> argLimit = std::nullopt);

        std::string getName() const { return m_name; }
        std::string getHelpText() const { return m_helpText; }
        util::Input getInput() const { return m_input; }
        std::optional<unsigned int> getArgLimit() const { return m_argLimit; }

        void perform();

    private:
        const std::string m_name;
        const std::string m_helpText;
        const util::Input m_input;
        const std::optional<unsigned int> m_argLimit;

        virtual void run() = 0;
};

} // namespace action

#endif
