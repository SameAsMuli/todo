#include <filesystem> //std::filesystem

#include "action/action_abstract.hpp"

#ifndef VIEW_FUNCTION_H
#define VIEW_FUNCTION_H

namespace action {

class View : public ActionAbstract {

    public:
        View(const util::Input& input);

        void run() override;

        void archiveTodos() const;

        void doneTodos() const;

        void lowTodos() const;

        void normalTodos() const;

        void rejectTodos() const;

        void urgentTodos() const;

    private:
        void viewTodos(const std::filesystem::path& file) const;
};

#endif

} // namespace action
