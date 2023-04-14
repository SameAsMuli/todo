#include <algorithm> // std::count
#include <fstream>   // std::istreambuf_iterator
#include <variant>
#include <vector> // std::vector

#include "util/file.hpp"

namespace util {

File::File(const std::filesystem::path &file) : m_file{file} {};

unsigned int File::line_count() {
    auto count = std::count(std::istreambuf_iterator<char>(this->m_file),
                            std::istreambuf_iterator<char>(), '\n');
    this->m_file.clear();
    this->m_file.seekg(0);
    return count;
}

std::vector<std::string> File::search(const std::string &string) {
    /* TODO: Split file into chunks for different threads */
    /* auto max_threads = std::thread::hardware_concurrency(); */

    std::string line;
    std::vector<std::string> matching_lines;
    while (std::getline(this->m_file, line)) {
        if (line.find(string) != std::string::npos) {
            matching_lines.push_back(line);
        }
    }
    return matching_lines;
}

} // namespace util
