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
        if (current++ == end) {
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
        if ((x + dirX) > 7 || (x + dirX) < 0) {
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
        if ((y + dirY) < 0) {
            return y;
        } else {
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
        {2, {{0, 0}, {1, 0}, {1, 0}, {1, 1}}}
    };

    repeating_iterator<const formation*> current_formation = {&formations[0], &formations[5]};
    repeating_iterator<std::string::const_iterator> current_jet = {lines[0].cbegin(), lines[0].cend()};

    int currentHeight = 0;
    std::set<rock> rocks;
    for (int i = 0; i < 2023; i++) {
        int y = std::max_element(rocks.begin(), rocks.end())->y + 3;
        int x = 2;

        while (true) {
            x = moveRocks(rocks, *current_formation, x, y, *current_jet++);

            if (moveRocks(rocks, *current_formation, x, y, 'v') == y) {
                for (auto& r : current_formation->rocks) {
                    rocks.insert(r + rock({x, y}));
                }
                break;
            } else {
                y++;
            }
        }
    }

    std::cout << std::endl << std::endl << std::endl;
}
