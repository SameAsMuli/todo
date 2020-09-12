#ifndef ACTION_ADD_ABSTRACT_H
#define ACTION_ADD_ABSTRACT_H

#include <filesystem> // std::filesystem

#include "action/action_abstract.hpp"
#include "task/task_type_abstract.hpp"

namespace action {

class AddAbstract : public ActionAbstract {

  public:
    AddAbstract(const std::string &name, const std::string &helpText,
                const util::Input &input,
                task::TaskTypeAbstract *const taskType);

  private:
    task::TaskTypeAbstract *const m_taskType;

    void run() override;
};

} // namespace action

#endif
