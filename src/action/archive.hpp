#ifndef ACTION_ARCHIVE_H
#define ACTION_ARCHIVE_H

#include "action/action_abstract.hpp"
#include "util/input.hpp"

namespace action {

/**
 * @brief Action to archive all tasks in the complete data file.
 */
class Archive : public ActionAbstract {

  public:
    /**
     * @brief Initialise the archive action.
     *
     * @param input The user's input.
     */
    Archive(util::Input input);

    /**
     * @brief Move all complete tasks to the archive data file.
     */
    void run() override;
};

#endif

} // namespace action
