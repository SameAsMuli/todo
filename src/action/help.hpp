#ifndef ACTION_HELP_H
#define ACTION_HELP_H

#include <vector> // std::vector

#include "action/action_abstract.hpp"
#include "util/input.hpp"

namespace action {

class Help : public ActionAbstract {

    public:
        Help(util::Input input);

        void addFunctions( std::vector<ActionAbstract*>& functions);

        void run() override;

    private:
        std::vector<ActionAbstract*> m_functions;

        static bool todoFuncComp(
                ActionAbstract* tf1,
                ActionAbstract* tf2 );
};

#endif

} // namespace action
