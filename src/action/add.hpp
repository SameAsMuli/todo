#include "action/action_abstract.hpp"
#include "env/todofiles.hpp"
#include "util/inputparser.hpp"

#ifndef ADD_FUNCTION_H
#define ADD_FUNCTION_H

namespace action {

class Add : public ActionAbstract {

    public:
        Add(const TodoFiles& todoFiles, const util::InputParser& input);

        void run() override;

    private:
        util::InputParser m_input;
        TodoFiles   m_todoFiles;
};

#endif

} // namespace action
