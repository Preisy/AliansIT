#include "IStreamReadlineIterator.h"
#include <string>

IStreamReadlineIterator::IStreamReadlineIterator(
        IStreamReadlineIterator::istream_type & stream
) : is(std::addressof(stream)) {
    ++*this;
}

IStreamReadlineIterator::IStreamReadlineIterator(const IStreamReadlineIterator & other) = default;

const IStreamReadlineIterator::value_type & IStreamReadlineIterator::operator*() const {
    return recent;
}

const IStreamReadlineIterator::value_type* IStreamReadlineIterator::operator->() const {
    return std::addressof(recent);
}

IStreamReadlineIterator & IStreamReadlineIterator::operator++() {
    if (is != nullptr && is->eof()) {
        recent = "";
        is = nullptr;
    } else if (is != nullptr) std::getline(*is, recent);
    return *this;
}

IStreamReadlineIterator IStreamReadlineIterator::operator++(int) {
    auto buf = *this;
    ++*this;
    return buf;
}

bool IStreamReadlineIterator::operator==(const IStreamReadlineIterator & rhs) const {
    return recent == rhs.recent && is == rhs.is;
}

bool IStreamReadlineIterator::operator!=(const IStreamReadlineIterator & rhs) const {
    return !(*this == rhs);
}
