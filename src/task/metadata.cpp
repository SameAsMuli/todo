#include <iomanip> // std::get_time
#include <sstream> // std::stringstream
#include <string>  // std::string
#include <time.h>  // std::strftime, std::time_t

#include "task/metadata.hpp"
#include "task/prefix.hpp"

namespace {

static const char *DATE_TIME_FORMAT = "%F %T";
static const size_t DATE_TIME_LEN = 20;
static const char DELIMITER = ';';

} // namespace

namespace task {

Metadata::Metadata() : m_previousPrefix(' ') {}

std::istream &operator>>(std::istream &stream, Metadata &metadata) {
    std::string previousPrefix;
    std::string timestamp;
    std::tm tm = {};

    if (std::getline(stream, timestamp, DELIMITER) &&
        std::getline(stream, previousPrefix, DELIMITER)) {
        /* Decode the timestamp */
        std::stringstream ss{timestamp};
        ss >> std::get_time(&tm, DATE_TIME_FORMAT);
        if (ss.fail()) {
            stream.setstate(std::ios::failbit);
            return stream;
        }
        metadata.m_timeAdded =
            std::chrono::system_clock::from_time_t(std::mktime(&tm));

        /* Decode the previous prefix */
        metadata.m_previousPrefix.setCharacter(previousPrefix[0]);
    } else {
        /* One operation failed so set the state on the main stream to
         * indicate failure. */
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, Metadata metadata) {
    /* Output the time added to the stream */
    std::time_t timer =
        std::chrono::system_clock::to_time_t(metadata.getTimeAdded());
    char timestamp[DATE_TIME_LEN];

    std::strftime(timestamp, DATE_TIME_LEN, DATE_TIME_FORMAT,
                  std::localtime(&timer));

    stream << timestamp << DELIMITER;

    /* Output the previous task prefix to the stream */
    stream << metadata.getPreviousPrefix() << DELIMITER;

    return stream;
}

} // namespace task
