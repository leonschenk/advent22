#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <functional>

struct range {
    int min;
    int max;

    friend bool operator<(const range& first, const range& second) {
        if (first.min == second.min) {
            return first.max < second.max;
        } else {
            return first.min < second.min;
        }
    }

    friend std::ostream& operator<<(std::ostream& out, const range& r) {
        return out << "[" << r.min << "," << r.max << "]";
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::vector<range> ranges;
    std::set<int> beacons;

    const int lineOfInterest = 2000000;

    for (auto& line : lines) {
        std::string word;
        char var, equals, comma;

        int sensorX, sensorY, beaconX, beaconY;

        std::stringstream str = std::stringstream(line);
        str >> word >> word;
        str >> var >> equals >> sensorX >> comma;
        str >> var >> equals >> sensorY;
        str >> word >> word >> word >> word >> word;
        str >> var >> equals >> beaconX >> comma;
        str >> var >> equals >> beaconY;

        std::cout << "Sensor at x=" << sensorX << ", y=" << sensorY;
        std::cout << ": closest beacon is at x=" << beaconX << ", y=" << beaconY << std::endl;

        int distance = abs(sensorX - beaconX) + abs(sensorY - beaconY);
        int distanceToY10 = abs(sensorY - lineOfInterest);
        int numberOfOverlap = distance - distanceToY10;
        std::cout << "Distance: " << distance << " to row y= " << lineOfInterest << " " << distanceToY10 << " overlap " << numberOfOverlap << std::endl;
        if (numberOfOverlap >= 0) {
            std::cout << "Range is " << (sensorX - numberOfOverlap) << " to " << (sensorX + numberOfOverlap + 1) << std::endl;
            ranges.push_back({sensorX - numberOfOverlap, sensorX + numberOfOverlap + 1});
        }
        if (beaconY == lineOfInterest) {
            beacons.insert(beaconX);
        }
    }

    std::sort(ranges.begin(), ranges.end());

    int last = -1000000;
    int totalCount = -beacons.size();
    for (auto& r : ranges) {
        std::cout << r << std::endl;
        if (r.min <= last) {
            if (r.max > last) {
                totalCount += (r.max - last);
                std::cout << "Score increased by " << (r.max - last) << std::endl;
            }
        } else {
            totalCount += (r.max - r.min);
            std::cout << "Score increased by " << (r.max - r.min) << std::endl;
        }
        last = std::max(last, r.max);
        std::cout << "Last added is " << last << " score increased to " << totalCount << std::endl;
    }

    std::cout << "Final score is: " << totalCount << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
