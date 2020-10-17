#include <cctype> // std::isspace
#include <cstdio> // EOF

#include "task/prefix.hpp"

namespace todo {
namespace task {

const char Prefix::NULL_PREFIX = ' ';

Prefix::Prefix() : m_character(Prefix::NULL_PREFIX) {}

Prefix::Prefix(char character) : m_character(character) {}

void Prefix::setCharacter(char character) {
    /* Map any empty or whitespace character to NULL_PREFIX */
    if (character == '\0' || isspace(character)) {
        this->m_character = Prefix::NULL_PREFIX;
    } else {
        this->m_character = character;
    }
}

bool Prefix::operator==(Prefix prefix) {
    return this->m_character == prefix.m_character;
}

std::istream &operator>>(std::istream &stream, Prefix &prefix) {
    auto character = stream.get();

    if (character == EOF) {
        /* Stream is empty when it wasn't expected it to be, so set the failbit
         */
        stream.setstate(std::ios::failbit);
    } else {
        prefix.setCharacter(character);
    }

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Prefix &prefix) {
    stream << prefix.m_character;
    return stream;
}

} // namespace task
} // namespace todo
