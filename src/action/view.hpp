#ifndef ACTION_VIEW_H
#define ACTION_VIEW_H

#include <filesystem> //std::filesystem

#include "action/action_abstract.hpp"
#include "task/task_type_abstract.hpp"

namespace action {

class View : public ActionAbstract {

  public:
    View(const util::Input &input);

    void run() override;

    void completeTodos() const;

    void outstandingTodos() const;

    void archiveTodos() const;

    void doneTodos() const;

    void lowTodos() const;

    void normalTodos() const;

    void rejectTodos() const;

    void urgentTodos() const;

  private:
    void viewTodos(task::TaskTypeAbstract *const taskType) const;
};

#endif

} // namespace action
