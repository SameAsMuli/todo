#include <filesystem> //std::filesystem

#include "action/action_abstract.hpp"

#ifndef VIEW_FUNCTION_H
#define VIEW_FUNCTION_H

namespace action {

class View : public ActionAbstract {

    public:
        View(const util::Input& input);

        void run() override;

        void archiveTodos();

        void doneTodos();

        void lowTodos();

        void normalTodos();

        void rejectTodos();

        void urgentTodos();

    private:
        void viewTodos(const std::filesystem::path& file);
};

#endif

} // namespace action
