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

    friend std::ostream& operator<<(std::ostream& output, const char2& p) {
        return output << '\'' << p.first << p.second << '\'';
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

int calc(const int n, const char2 pos, const char2 posElephant, const int togo, const int togoElephant, std::map<char2, bool>& toDo) {
    if (n >= 30) {
        return 0;
    }

    if (n <= 10) {
        std::cout << "n == " << n << " try " << pos << " and " << posElephant << std::endl;
    }

    int currentNodeValue = 0;
    const bool meFinished = togo == 0;
    const bool elephantFinished = togoElephant == 0;
    if (meFinished) {
        currentNodeValue += (30 - n) * flows[pos];
    } else if (elephantFinished) {
        currentNodeValue += (30 - n) * flows[posElephant];
    }

    std::vector<char2> currentToDo;
    for (auto& next : toDo) {
        if (next.second) {
            currentToDo.push_back(next.first);
        }
    }
    if (currentToDo.empty() && meFinished && elephantFinished) {
        return currentNodeValue;
    } else {
        int max = 0;
        if (meFinished) {
            for (auto& next : currentToDo) {
                int pathLength = vals[pos][next];
                int stepSize = std::max(std::min(togoElephant, pathLength + 1), 0);
                toDo[next] = false;
                int val = calc(n + stepSize, next, posElephant, pathLength + 1 - stepSize, togoElephant - stepSize, toDo);
                toDo[next] = true;
                max = std::max(max, val);
            }
            int val = calc(n + togoElephant, pos, posElephant, 10000, 0, toDo);
            max = std::max(max, val);
        } else if (elephantFinished) {
            for (auto& next : currentToDo) {
                int pathLength = vals[posElephant][next];
                int stepSize = std::max(std::min(togo, pathLength + 1), 0);
                toDo[next] = false;
                int val = calc(n + stepSize, pos, next, togo - stepSize, pathLength + 1 - stepSize, toDo);
                toDo[next] = true;
                max = std::max(max, val);
            }
            int val = calc(n + togo, pos, posElephant, 0, 10000, toDo);
            max = std::max(max, val);
        } else {
            throw "Dit is foute boel!";
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

    int value = calc(4, char2("AA"), char2("AA"), 0, 0, toDo);

    std::cout << "Max value: " << value << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
