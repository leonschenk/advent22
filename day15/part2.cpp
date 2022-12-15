#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <functional>

struct sensor {
    int x;
    int y;
    int range;

    friend std::ostream& operator<<(std::ostream& out, const sensor& r) {
        return out << "[" << r.x << "," << r.y << ":" << r.range << "]";
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::vector<sensor> ranges;

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
        ranges.push_back({sensorX, sensorY, distance});
    }

    std::sort(ranges.begin(), ranges.end(), [] (const sensor& first, const sensor& second) {
        return first.range > second.range;
    });

    std::cout << std::endl;

    const int max = 4000000;
    const int multiplier = 4000000;
    for (int y = 0; y <= max; y++) {
        for (int x = 0; x <= max; x++) {
            bool isFound = true;
            for (auto& sensor : ranges) {
                int distanceX = abs(x - sensor.x);
                int distanceY = abs(y - sensor.y);
                if ((distanceX + distanceY) <= sensor.range) {
                    x = sensor.x - distanceY + sensor.range;
                    isFound = false;
                    break;
                }
            }
            if (isFound) {
                std::cout << "Found! (" << x << ", " << y << ")" << std::endl;
                std::cout << "Score is " << (((long) x * (long) multiplier) + (long) y) << std::endl;
                return 0;
            }
        }
    }

    std::cout << std::endl << std::endl << std::endl;
}
