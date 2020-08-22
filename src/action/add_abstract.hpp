#include <filesystem> // std::filesystem

#include "action/action_abstract.hpp"

#ifndef ADD_ABSTRACT_H
#define ADD_ABSTRACT_H

namespace action {

class AddAbstract : public ActionAbstract {

    public:
        AddAbstract(
                const std::string& name,
                const std::string& helpText,
                const util::Input& input,
                const std::filesystem::path& file,
                const std::string& prefix);

        std::string getPrefix() const { return m_prefix; }

        void run() override;

    private:
        const std::filesystem::path m_file;
        const std::string m_prefix;
};

} // namespace action

#endif
