#include <iostream>
#include <regex>
#include <string_view>
#include <vector>
#include <charconv>


const std::vector<std::regex> patterns{
        std::regex(R"(^[A-Z][A-Z][A-Z])"),
        std::regex(R"(^[A-Z][A-Z]\s)"),
        std::regex(R"(^[A-Z][A-Z])"),
        std::regex(R"(^[A-Z][A-Z0-9]\s|[A-Z0-9][A-Z]\s)"),
        std::regex(R"(^[A-Z][A-Z0-9]|[A-Z0-9][A-Z])"),
        std::regex(R"(^)"),
};

std::string::const_iterator findEndOfAirlineCode(const std::string & str) {
    for (const auto & it: patterns) {
        auto sri = std::sregex_iterator(str.begin(), str.end(), it);
        if (!sri->empty()) return str.begin() + sri->length();
    }
    return str.end();
}

int getFlightNumber(std::string_view str) {
    int num = 0;
    std::from_chars(str.data(), str.data() + str.length(), num);
    return num;
}

std::pair<std::string_view, int> getFlightData(const std::string & str) {
    auto endOfAirlineCode = findEndOfAirlineCode(str);

    std::string_view airLineCode = std::string_view(str.begin(), endOfAirlineCode);
    if (!airLineCode.empty() && airLineCode.ends_with(' '))
        airLineCode = std::string_view(str.begin(), endOfAirlineCode - 1);

    auto strFlightNumber = std::string_view(endOfAirlineCode, str.end());
    return {airLineCode, getFlightNumber(strFlightNumber)};
}

bool compare(const std::string & str1, const std::string & str2) {
    auto flightData1 = getFlightData(str1);
    auto flightData2 = getFlightData(str2);
    return flightData1 == flightData2;
}


int main() {
    int res = compare("25", "025");
    std::cout << "res: " << res << std::endl;

    return 0;
}
