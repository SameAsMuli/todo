#include <string> // std::string
#include <vector> // std::vector

#ifndef INPUT_H
#define INPUT_H

namespace util {

class Input {

    public:
        Input(int argc, char const* const * argv);

        std::vector<std::string>::size_type size() const;

        bool isEmpty() const;

        bool hasOption(const std::string& option) const;

        bool hasOption(
                std::vector<std::string>::size_type index) const;

        bool hasOption(const std::string& option,
                std::vector<std::string>::size_type index) const;

        std::string getOption(
                std::vector<std::string>::size_type index) const;

    private:
        std::vector<std::string> m_tokens;
};

} // namespace util

#endif
