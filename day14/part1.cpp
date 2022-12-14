#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <functional>

struct point {
    int x;
    int y;

    friend bool operator<(const point& a, const point& b) {
        if (a.y == b.y) {
            return a.x < b.x;
        } else {
            return a.y < b.y;
        }
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    int minx = 99999, maxx = -99999, miny = 0, maxy = 0;
    std::set<point> rocks;

    for (auto& line : lines) {
        std::stringstream str = std::stringstream(line);
        int x, y;
        int cursorx, cursory;
        char charPad;
        if (str >> cursorx >> charPad >> cursory) {
            minx = std::min(minx, cursorx);
            maxx = std::max(maxx, cursorx);
            str >> charPad >> charPad;
            while (str >> x >> charPad >> y) {
                minx = std::min(minx, x);
                maxx = std::max(maxx, x);
                if (x == cursorx) {
                    for (int dy = 0; dy <= abs(cursory - y); dy++) {
                        rocks.insert({x, cursory + (cursory > y ? -dy : dy)});
                    }
                } else if (y == cursory) {
                    for (int dx = 0; dx <= abs(cursorx - x); dx++) {
                        rocks.insert({cursorx + (cursorx > x ? -dx : dx), y});
                    }
                } else {
                    throw "Invalid!";
                }
                cursorx = x;
                cursory = y;
                str >> charPad >> charPad;
            }
        }
    }

    miny = std::min(rocks.cbegin()->y, 0);
    maxy = std::max(rocks.crbegin()->y, 0);

    std::cout << "X: " << minx << " to " << maxx << std::endl;
    std::cout << "Y: " << miny << " to " << maxy << std::endl;

    auto a = rocks.cbegin();
    for (int i = miny; i <= maxy; i++) {
        for (int j = minx; j <= maxx; j++) {
            if (i == a->y && j == a->x) {
                std::cout << '#';
                a++;
            } else if (i == 0 && j == 500) {
                std::cout << '+';
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }

    int score = 0;
    int x = 500, y = 0;
    do {
        if (rocks.find({x, y + 1}) == rocks.end()) {
            y++;
        } else if (rocks.find({x - 1, y + 1}) == rocks.end()) {
            x--;
            y++;
        } else if (rocks.find({x + 1, y + 1}) == rocks.end()) {
            x++;
            y++;
        } else {
            rocks.insert({x, y});
            score++;
            x = 500;
            y = 0;
        }
    } while (y <= maxy);

    a = rocks.cbegin();
    for (int i = miny; i <= maxy; i++) {
        for (int j = minx; j <= maxx; j++) {
            if (i == a->y && j == a->x) {
                std::cout << '#';
                a++;
            } else if (i == 0 && j == 500) {
                std::cout << '+';
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Final score is: " << score << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
