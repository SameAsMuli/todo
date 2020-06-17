#include <string> // std::string
#include <vector> // std::vector

#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

class InputParser {

    public:
        InputParser(int argc, char const* const * argv);

        bool isEmpty() const;

        bool hasOption(const std::string& option) const;

        bool hasOption(
                std::vector<std::string>::size_type index) const;

        bool hasOption(const std::string& option,
                std::vector<std::string>::size_type index) const;

        std::string getOption(
                std::vector<std::string>::size_type index) const;

    private:
        std::vector<std::string> tokens;
};

#endif
