#ifndef UTIL_INPUT_H
#define UTIL_INPUT_H

#include <string> // std::string
#include <vector> // std::vector

namespace util {

class Input {

  public:
    Input(int argc, char const *const *argv);

    static const std::vector<std::string>::size_type ACTION_INDEX;

    static const std::vector<std::string>::size_type PARAM_START_INDEX;

    std::vector<std::string>::size_type size() const;

    bool isEmpty() const;

    bool hasOption(const std::string &option) const;

    bool hasOption(std::vector<std::string>::size_type index) const;

    bool hasOption(const std::string &option,
                   std::vector<std::string>::size_type index) const;

    std::string getOption(std::vector<std::string>::size_type index) const;

    std::string toString(std::vector<std::string>::size_type index) const;

  private:
    std::vector<std::string> m_tokens;
};

} // namespace util

#endif
