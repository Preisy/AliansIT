#include <iostream>
#include <unordered_set>
#include <thread>
#include <set>

#include "IStreamReadlineIterator.h"
#include "CompareInteractor.h"

class FlightIdComparator {
    CompareInteractor compareInteractor;
public:
    FlightIdComparator() = default;

    explicit FlightIdComparator(const CompareInteractor & compareInteractor) : compareInteractor(compareInteractor) {}

    bool operator()(const std::string & lhs, const std::string & rhs) const {
        auto res = compareInteractor.compare(lhs, rhs);
        if (res) return false;
        else return lhs > rhs;
    }
};

auto processData(const std::string & ifilename, const std::string & ofilename) {
    return [=]() {
        std::ifstream ifs(ifilename, std::ios::in);
        std::set<std::string, FlightIdComparator> set;
        std::copy(IStreamReadlineIterator(ifs), IStreamReadlineIterator(), std::inserter(set, std::end(set)));
        ifs.close();

        std::ofstream ofs(ofilename);
        std::copy(std::begin(set), std::end(set), std::ostream_iterator<std::string>(ofs, "\n"));
        ofs.close();
    };
}

int main() {
    FlightIdComparator flightIdComparator;
    CompareInteractor compareInteractor;

    auto t1 = std::thread(processData(
            "/mnt/d/C/practice/AliansIT/task2/1_in.txt",
            "/mnt/d/C/practice/AliansIT/task2/1_out.txt"
    ));
    auto t2 = std::thread(processData(
            "/mnt/d/C/practice/AliansIT/task2/2_in.txt",
            "/mnt/d/C/practice/AliansIT/task2/2_out.txt"
    ));

    t1.join();
    t2.join();

    return 0;
}
