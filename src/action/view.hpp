#include "action/action_abstract.hpp"

#ifndef VIEW_FUNCTION_H
#define VIEW_FUNCTION_H

namespace action {

class View : public ActionAbstract {

    public:
        View(const util::InputParser& input);

        void run() override;

        void archiveTodos();

        void doneTodos();

        void lowTodos();

        void normalTodos();

        void rejectTodos();

        void urgentTodos();
};

#endif

} // namespace action
