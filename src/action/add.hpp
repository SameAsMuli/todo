#include "action/action_abstract.hpp"
#include "util/inputparser.hpp"

#ifndef ADD_FUNCTION_H
#define ADD_FUNCTION_H

namespace action {

class Add : public ActionAbstract {

    public:
        Add(const util::InputParser& input);

        void run() override;

    private:
        util::InputParser m_input;
};

#endif

} // namespace action
