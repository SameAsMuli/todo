#include "action/action_abstract.hpp"
#include "env/todofiles.hpp"
#include "util/inputparser.hpp"

#ifndef VIEW_FUNCTION_H
#define VIEW_FUNCTION_H

namespace action {

class View : public ActionAbstract {

    public:
        View(
                const TodoFiles& todoFiles,
                const InputParser& input);

        void run() override;

        void archiveTodos();

        void doneTodos();

        void lowTodos();

        void normalTodos();

        void rejectTodos();

        void urgentTodos();

    private:
        InputParser m_input;
        TodoFiles   m_todoFiles;
};

#endif

} // namespace action
