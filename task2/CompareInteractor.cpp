#include "CompareInteractor.h"

#include <iostream>
#include <string_view>
#include <charconv>


std::string::const_iterator CompareInteractor::findEndOfAirlineCode(const std::string & str) const {
    for (const auto & it: patterns) {
        auto sri = std::sregex_iterator(str.begin(), str.end(), it);
        if (!sri->empty()) return str.begin() + sri->length();
    }
    return str.end();
}

int CompareInteractor::getFlightNumber(std::string_view str) const {
    int num = 0;
    std::from_chars(str.data(), str.data() + str.length(), num);
    return num;
}

std::pair<std::string_view, int> CompareInteractor::getFlightData(const std::string & str) const {
    auto endOfAirlineCode = findEndOfAirlineCode(str);

    std::string_view airLineCode = std::string_view(str.begin(), endOfAirlineCode);
    if (!airLineCode.empty() && airLineCode.ends_with(' '))
        airLineCode = std::string_view(str.begin(), endOfAirlineCode - 1);

    auto strFlightNumber = std::string_view(endOfAirlineCode, str.end());
    return {airLineCode, getFlightNumber(strFlightNumber)};
}

bool CompareInteractor::compare(const std::string & str1, const std::string & str2) const {
    auto flightData1 = getFlightData(str1);
    auto flightData2 = getFlightData(str2);
    return flightData1 == flightData2;
}
