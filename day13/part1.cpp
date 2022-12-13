#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <functional>

struct node {
public:
    bool isMarker;
    bool isValueNode;
    int value;
    std::vector<node> subNodes;

    node(bool isValueNode, int value) : isMarker(false), isValueNode(false), value(0), subNodes({node(value)}) {
    }

    node(int value) : isMarker(false), isValueNode(true), value(value), subNodes() {
    }

    node(bool isMarker, std::string::const_iterator& input) : isMarker(isMarker), isValueNode(false), value(0), subNodes() {
        if (*input == '[') {
            // list;
            input++;
            while (*input != ']') {
                if (*input == ',') {
                    input++;
                } else {
                    subNodes.push_back(node(false, input));
                }
            }
            input++;
        } else {
            // integer
            size_t a;
            isValueNode = true;
            value = std::stoi(input.base(), &a);
            input += a;
        }
    }

    bool operator<(const node& other) const {
        std::cout << "- Compare " << *this << " vs " << other << std::endl;
        if (this->isValueNode && other.isValueNode) {
            return this->value < other.value;
        } else if (!(this->isValueNode || other.isValueNode)) {
            auto j = other.subNodes.cbegin();
            for (auto i = this->subNodes.cbegin(); i != this->subNodes.cend(); i++) {
                if (j != other.subNodes.cend()) {
                    if ((*i) < (*j)) {
                        return true;
                    } else if ((*j) < (*i)) {
                        return false;
                    }
                    j++;
                } else {
                    return false;
                }
            }
            return j != other.subNodes.cend();
        } else if (this->isValueNode) {
            return node(true, this->value) < other;
        } else {
            return *this < node(true, other.value);
        }
    }

    friend std::ostream& operator<<(std::ostream& t, const node& node) {
        if (node.isValueNode) {
            t << node.value;
        } else {
            t << '[';
            for (auto i = node.subNodes.cbegin(); i != node.subNodes.cend(); i++) {
                t << (*i);
                if ((i + 1) != node.subNodes.cend()) {
                    t << ',';
                }
            }
            t << ']';
        }
        return t;
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::string::const_iterator two = std::string("[[2]]").cbegin();
    std::string::const_iterator six = std::string("[[6]]").cbegin();

    std::vector<node> nodes = {node(true, two), node(true, six)};
    for (auto& line : lines) {
        std::string::const_iterator it = line.cbegin();
        if (it != line.cend()) {
            nodes.push_back(node(false, it));
        }
    }

    for (auto& node : nodes) {
        std::cout << node << std::endl;
    }

    std::sort(nodes.begin(), nodes.end());

    int totalScore = 1;
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].isMarker) {
            totalScore *= (i + 1);
        }
        std::cout << nodes[i] << std::endl;
    }

    std::cout << std::endl << "Score of the indices is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
