#include <filesystem> // std::filesystem

#include "action/action_abstract.hpp"
#include "util/inputparser.hpp"

#ifndef ADD_ABSTRACT_H
#define ADD_ABSTRACT_H

namespace action {

class AddAbstract : public ActionAbstract {

    public:
        AddAbstract(
                const std::string&           name,
                const std::string&           helpText,
                const util::InputParser&     input,
                const std::filesystem::path& file,
                const std::string&           prefix);

        std::string getPrefix() { return m_prefix; }

        void run() override;

    private:
        util::InputParser     m_input;
        std::filesystem::path m_file;
        std::string           m_prefix;
};

} // namespace action

#endif
