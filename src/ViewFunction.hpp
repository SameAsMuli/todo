#include <filesystem> // std::filesystem

#include "InputParser.hpp"
#include "TodoFunctionAbstract.hpp"

#ifndef VIEW_FUNCTION_H
#define VIEW_FUNCTION_H

namespace fs = std::filesystem;

class ViewFunction : public TodoFunctionAbstract {

    public:
        ViewFunction(
                const fs::path& todoFile,
                const InputParser& input);

        void run() override;

    private:
        InputParser m_input;
        fs::path    m_todoFile;
};

#endif
