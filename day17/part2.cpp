#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <map>
#include <functional>

struct rock {
    const int x;
    const int y;

    friend rock operator+(const rock& left, const rock& right) {
        return {left.x + right.x, left.y + right.y};
    }

    friend bool operator<(const rock& left, const rock& right) {
        if (left.y < right.y) {
            return true;
        } else if (left.y == right.y) {
            return left.x < right.x;
        } else {
            return false;
        }
    }
};

struct formation {
    const int width;
    const std::set<rock> rocks;
};

template<typename T> struct repeating_iterator {
    const T begin;
    const T end;
    T current = begin;

    repeating_iterator& operator++(int) {
        if (++current == end) {
            current = begin;
        }
        return *this;
    }

    const auto& operator*() {
        return *current;
    }

    auto* operator->() {
        return current;
    }
};

int moveRocks(const std::set<rock>& rocks, const formation& form, int x, int y, char move) {
    const int dirX = move == '<' ? -1 : (move == '>' ? 1 : 0);
    if (dirX) {
        if ((x + dirX + form.width) > 7 || (x + dirX) < 0) {
            return x;
        } else {
            for (auto& j : form.rocks) {
                if (rocks.find(j + rock({x + dirX, y})) != rocks.end()) {
                    return x;
                }
            }
            return x + dirX;
        }
    }
    const int dirY = move == 'v' ? -1 : 0;
    if (dirY) {
        if ((y + dirY) <= 0) {
            return y;
        } else {
            const int maxY = rocks.empty() ? 0 : rocks.rbegin()->y;
            if (y + dirY > maxY) {
                return y + dirY;
            }
            for (auto& j : form.rocks) {
                if (rocks.find(j + rock({x, y + dirY})) != rocks.end()) {
                    return y;
                }
            }
            return y + dirY;
        }
    }
    throw "Dit is niet best!";
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    const formation formations[5] = {
        {4, {{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
        {3, {{1, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}}},
        {3, {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}}},
        {1, {{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
        {2, {{0, 0}, {1, 0}, {0, 1}, {1, 1}}}
    };

    repeating_iterator<const formation*> current_formation = {&formations[0], &formations[5]};
    repeating_iterator<std::string::const_iterator> current_jet = {lines[0].cbegin(), lines[0].cend()};

    long period = lines[0].length();
    long totalRounds = 1000000000000;

    long multiplier = totalRounds / period;
    long rest = totalRounds % period;

    int currentHeight = 0;
    std::set<rock> rocks;
    std::map<int, int> heights;
    for (int i = 0; i < (period * 10 * 4); i++) {
        int y = rocks.empty() ? 4 : rocks.rbegin()->y + 4;
        int x = 2;
        while (true) {
            x = moveRocks(rocks, *current_formation, x, y, *current_jet);
            current_jet++;

            const int ytemp = moveRocks(rocks, *current_formation, x, y, 'v');
            if (y == ytemp) {
                for (auto& r : current_formation->rocks) {
                    rocks.insert(r + rock({x, y}));
                }
                break;
            } else {
                y = ytemp;
            }
        }
        current_formation++;
        heights[i] = rocks.rbegin()->y;
    }

    for (int i = 1000; i < period * 10; i++) {
        long diff = heights[i*4] - heights[i*3];
        long diff2 = heights[i*3] - heights[i*2];
        long diff3 = heights[i*2] - heights[i];
        if ((diff == diff2) && (diff == diff3)) {
            std::cout << "Gevonden: " << i << ": " << diff << " (";
            long rest = 1000000000000 % i;
            long mult = 1000000000000 / i;
            long res = diff * (mult - 4) + heights[(i*4) + rest] - 1;
            std::cout << res << ")" << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << "Rest " << (rocks.rbegin()->y - heights.rbegin()->second) << " additional units!" << std::endl;
    std::cout << "Tower is " << rocks.rbegin()->y << " units tall!" << std::endl;

    long diff = heights[2] - heights[1];
    long answer = diff * (multiplier - 4) + rocks.rbegin()->y;

    std::cout << "Answer is " << answer << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
