#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <set>
#include <functional>

struct Point {
    int x = 0;
    int y = 0;

    bool operator<(const Point& other) const {
        if (x < other.x) {
            return true;
        } else if (x == other.x) {
            if (y < other.y) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

void updateTail(const Point& head, Point& tail) {
    int distancex = head.x - tail.x;
    int distancey = head.y - tail.y;

    if (abs(distancex) <= 1 && abs(distancey) <= 1) {
        return;
    }

    if (distancex > 0) {
        tail.x++;
        std::cout << '>';
    } else if (distancex < 0) {
        tail.x--;
        std::cout << '<';
    }
    if (distancey > 0) {
        tail.y++;
        std::cout << '^';
    } else if (distancey < 0) {
        tail.y--;
        std::cout << '.';
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::set<Point> positions;

    const int knots = 10;
    std::array<Point, knots> rope;

    std::set<Point> pointsVisited;

    for (auto& line : lines) {
        std::stringstream str = std::stringstream(line);
        char direction;
        int positions;

        str >> direction >> positions;

        std::cout << line << std::endl;

        switch (direction) {
            case 'R':
                for (int i = 0; i < positions; i++) {
                    rope[0].x++;
                    for (int j = 1; j < knots; j++) {
                        updateTail(rope[j-1], rope[j]);
                    }
                    pointsVisited.insert(rope[knots-1]);
                }
                break;
            case 'U':
                for (int i = 0; i < positions; i++) {
                    rope[0].y++;
                    for (int j = 1; j < knots; j++) {
                        updateTail(rope[j-1], rope[j]);
                    }
                    pointsVisited.insert(rope[knots-1]);
                }
                break;
            case 'L':
                for (int i = 0; i < positions; i++) {
                    rope[0].x--;
                    for (int j = 1; j < knots; j++) {
                        updateTail(rope[j-1], rope[j]);
                    }
                    pointsVisited.insert(rope[knots-1]);
                }
                break;
            case 'D':
                for (int i = 0; i < positions; i++) {
                    rope[0].y--;
                    for (int j = 1; j < knots; j++) {
                        updateTail(rope[j-1], rope[j]);
                    }
                    pointsVisited.insert(rope[knots-1]);
                }
                break;
        }

        std::cout << std::endl << "Head (" << rope[0].x << "," << rope[0].y << ")" << std::endl << "tail (" << rope[knots - 1].x << "," << rope[knots-1].y << ")" << std::endl;
    }
    std::cout << "Final score: " << pointsVisited.size() << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
