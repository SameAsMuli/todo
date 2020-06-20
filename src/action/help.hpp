#include <vector> // std::vector

#include "action/action_abstract.hpp"
#include "util/inputparser.hpp"

#ifndef HELP_FUNCTION_H
#define HELP_FUNCTION_H

namespace action {

class Help : public ActionAbstract {

    public:
        Help();

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
