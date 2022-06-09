#ifndef ACTION_ARCHIVE_H
#define ACTION_ARCHIVE_H

#include "action/action_abstract.hpp"
#include "input/input.hpp"

namespace todo {
namespace action {

/**
 * @brief Action to archive all tasks in the complete data file.
 */
class Archive : public ActionAbstract {

  public:
    /**
     * @brief Initialise the archive action.
     */
    Archive();

    /**
     * @brief Get a detailed description of the archive action.
     *
     * @return A string with the description of the archive action.
     */
    std::string description() const override;

    /**
     * @brief Get the usage details of the archive action.
     *
     * @return A string with the usage text of the archive action.
     */
    std::string usage() const override;

  private:
    /**
     * @brief Move all complete tasks to the archive data file.
     */
    void run(const input::Input &input) override;
};

#endif

} // namespace action
} // namespace todo
