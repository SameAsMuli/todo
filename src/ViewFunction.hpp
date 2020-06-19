#include "InputParser.hpp"
#include "TodoFiles.hpp"
#include "TodoFunctionAbstract.hpp"

#ifndef VIEW_FUNCTION_H
#define VIEW_FUNCTION_H

class ViewFunction : public TodoFunctionAbstract {

    public:
        ViewFunction(
                const TodoFiles& todoFiles,
                const InputParser& input);

        void run() override;

        void archiveTodos();

        void doneTodos();

        void lowTodos();

        void normalTodos();

        void rejectTodos();

        void urgentTodos();

    private:
        InputParser m_input;
        TodoFiles   m_todoFiles;
};

#endif
