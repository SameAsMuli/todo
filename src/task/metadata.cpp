#include <iomanip> // std::get_time
#include <sstream> // std::stringstream
#include <string>  // std::string
#include <time.h>  // std::strftime, std::time_t

#include "task/metadata.hpp"
#include "task/prefix.hpp"

namespace {

static const char DELIMITER = ';';

} // namespace

namespace todo {
namespace task {

Metadata::Metadata() : m_previousPrefix(Prefix::NULL_PREFIX) {}

std::istream &operator>>(std::istream &stream, Metadata &metadata) {
    std::string previousPrefix;
    std::string previousTimestamp;
    std::string timestamp;
    std::time_t time;

    if (std::getline(stream, timestamp, DELIMITER) &&
        std::getline(stream, previousPrefix, DELIMITER) &&
        std::getline(stream, previousTimestamp, DELIMITER)) {
        /* Decode the time added timestamp */
        std::stringstream ss{timestamp};
        ss >> time;
        if (ss.fail()) {
            stream.setstate(std::ios::failbit);
            return stream;
        }
        metadata.m_timeAdded = std::chrono::system_clock::from_time_t(time);

        /* Decode the previous prefix */
        metadata.m_previousPrefix.setCharacter(previousPrefix[0]);

        /* Decode the previous time added timestamp */
        ss = std::stringstream{previousTimestamp};
        ss >> time;
        if (ss.fail()) {
            stream.setstate(std::ios::failbit);
            return stream;
        }
        metadata.m_previousTimeAdded =
            std::chrono::system_clock::from_time_t(time);
    } else {
        /* One operation failed so set the state on the main stream to
         * indicate failure. */
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Metadata &metadata) {
    /* Output the time added to the stream */
    stream << std::chrono::system_clock::to_time_t(metadata.getTimeAdded())
           << DELIMITER;

    /* Output the previous task prefix to the stream */
    stream << metadata.getPreviousPrefix() << DELIMITER;

    /* Output the previous time added to the stream */
    stream << std::chrono::system_clock::to_time_t(
                  metadata.getPreviousTimeAdded())
           << DELIMITER;

    return stream;
}

} // namespace task
} // namespace todo
