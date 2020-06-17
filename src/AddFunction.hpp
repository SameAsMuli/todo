#include <filesystem> // std::filesystem

#include "InputParser.hpp"
#include "TodoFunctionAbstract.hpp"

#ifndef ADD_FUNCTION_H
#define ADD_FUNCTION_H

namespace fs = std::filesystem;

class AddFunction : public TodoFunctionAbstract {

    public:
        AddFunction(
                const fs::path& todoFile,
                const InputParser& input);

        void run() override;

    private:
        InputParser m_input;
        fs::path    m_todoFile;
};

#endif
