#pragma once

#include <fstream>
#include <iterator>


class IStreamReadlineIterator {
public:
    using istream_type = std::basic_istream<char>;
    using value_type = std::string;

private:
    std::basic_istream<char>* is = nullptr;
    value_type recent;

public:
    IStreamReadlineIterator() = default;

    explicit IStreamReadlineIterator(istream_type & stream);

    IStreamReadlineIterator(const IStreamReadlineIterator & other);

    const value_type & operator*() const;

    const value_type* operator->() const;

    IStreamReadlineIterator & operator++();

    IStreamReadlineIterator operator++(int);

    bool operator==(const IStreamReadlineIterator & rhs) const;

    bool operator!=(const IStreamReadlineIterator & rhs) const;
};

