#pragma once
#include <vector>
#include <regex>

class CompareInteractor {
    const std::vector<std::regex> patterns{
            std::regex(R"(^[A-Z][A-Z][A-Z])"),
            std::regex(R"(^[A-Z][A-Z]\s)"),
            std::regex(R"(^[A-Z][A-Z])"),
            std::regex(R"(^[A-Z][A-Z0-9]\s|[A-Z0-9][A-Z]\s)"),
            std::regex(R"(^[A-Z][A-Z0-9]|[A-Z0-9][A-Z])"),
            std::regex(R"(^)"),
    };

    [[nodiscard]] std::string::const_iterator findEndOfAirlineCode(const std::string & str) const;

    [[nodiscard]] int getFlightNumber(std::string_view str) const;

    [[nodiscard]] std::pair<std::string_view, int> getFlightData(const std::string & str) const;

public:
    [[nodiscard]] bool compare(const std::string & str1, const std::string & str2) const;
};
