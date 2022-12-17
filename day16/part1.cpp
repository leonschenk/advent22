#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <map>
#include <functional>

struct char2 {
    const char first;
    const char second;

    char2() : first(0), second(0) {
    }

    char2(const char chr) : first(chr), second(0) {
    }

    char2(const char first, const char second) : first(first), second(second) {
    }

    char2(const std::string& str) : first(str[0]), second(str[1]) {
    }

    friend std::istream& operator>>(std::istream& input, char2* p) {
        char a, b;
        input >> a >> b;
        new(p) char2(a, b);
        return input;
    }

    friend bool operator==(const char2& left, const char2& right) {
        return left.first == right.first && left.second == right.second;
    }

    friend bool operator<(const char2& left, const char2& right) {
        if (left.first < right.first) {
            return true;
        } else if (left.first == right.first) {
            return left.second < right.second;
        } else {
            return false;
        }
    }
};

std::map<char2, std::map<char2, int>> vals;
std::map<char2, int> flows;

int calc(const int n, const char2 pos, std::map<char2, bool>& toDo) {
    if (n >= 30) {
        return 0;
    }
    const int currentNodeValue = (30 - n) * flows[pos];
    if (toDo.empty()) {
        return currentNodeValue;
    } else {
        int max = 0;
        for (auto next = toDo.begin(); next != toDo.end(); next++) {
            if (next->second) {
                int pathLength = (next->first < pos) ? vals[next->first][pos] : vals[pos][next->first];
                next->second = false;
                int val = calc(n + pathLength + 1, next->first, toDo);
                next->second = true;
                max = std::max(max, val);
            }
        }
        return currentNodeValue + max;
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);
    std::map<char2, std::vector<char2>> nodes;

    std::vector<char2> names;

    for (auto& i : lines) {
        std::stringstream str = std::stringstream(i);
        std::string word;
        char2 name;
        char2 link;
        int flow;
        char semicolon, comma;
        str >> word >> &name >> word >> word >> word;
        flows[name] = std::stoi(word.substr(5));
        str >> word >> word >> word >> word;
        names.push_back(name);
        while (str >> &link) {
            nodes[link].push_back(name);
            nodes[name].push_back(link);
            str >> comma;
        }
    }

    for (const char2& name : names) {
        std::set<char2> visited;
        std::set<char2> notVisited;
        notVisited.insert(name);
        for (auto& l : nodes[name]) {
            notVisited.insert(l);
        }
        for (const char2& i : names) {
            if (i == name) {
                vals[name][i] = 0;
            } else {
                vals[name][i] = 10000;
            }
        }
        const char2* currentNode = &name;
        while (!notVisited.empty()) {
            for (auto& l : nodes[*currentNode]) {
                if (visited.find(l) == visited.end()) {
                    notVisited.insert(l);
                    int newDistance = vals[name][*currentNode] + 1;
                    vals[name][l] = std::min(newDistance, vals[name][l]);
                    vals[l][name] = std::min(newDistance, vals[name][l]);
                }
            }
            visited.insert(*currentNode);
            notVisited.erase(*currentNode);
            currentNode = &*std::min_element(notVisited.begin(), notVisited.end(), [name] (const char2& left, const char2& right) -> bool {
                return vals[name][left] < vals[name][right];
            });
        }
    }

    std::map<char2, bool> toDo;
    for (auto& i : flows) {
        if (i.second > 0) {
            toDo[i.first] = true;
        }
    }

    int value = calc(0, std::string("AA"), toDo);

    std::cout << "Max value: " << value << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
