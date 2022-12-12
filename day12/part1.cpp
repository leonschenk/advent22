#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <set>
#include <functional>

struct node {
    int xpos;
    int ypos;
    char height;
    bool visited;
    int tentativeDistance;

    char pos[4] = {' ', ' ', ' ', ' '};

    std::vector<node*> links;
};

char getHeight(std::vector<std::string>& lines, int xpos, int ypos) {
    int height = lines.size();
    int width = lines[0].length();
    if (xpos < 0 || ypos < 0 || xpos >= width || ypos >= height) {
        return '~';
    } else {
        return lines[ypos][xpos];
    }
}

char transform(char other) {
    if (other == 'S') {
        return 'a';
    } else if (other == 'E') {
        return 'z';
    } else {
        return other;
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    const int height = lines.size();
    const int width = lines[0].length();

    node* start;
    node* end;
    node** nodes = new node*[height];
    for (int i = 0; i < height; i++) {
        nodes[i] = new node[width];
    }

    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines[y].length(); x++) {
            char height = transform(getHeight(lines, x, y));

            char left = transform(getHeight(lines, x-1, y));
            char right = transform(getHeight(lines, x+1, y));
            char up = transform(getHeight(lines, x, y-1));
            char down = transform(getHeight(lines, x, y+1));

            if (getHeight(lines, x, y) == 'S') {
                start = &nodes[y][x];
                nodes[y][x] = {x, y, height, false, 0};
            } else if (getHeight(lines, x, y) == 'E') {
                end = &nodes[y][x];
                nodes[y][x] = {x, y, height, false, INT16_MAX};
            } else {
                nodes[y][x] = {x, y, height, false, INT16_MAX};
            }

            if (height + 1 >= left) {
                nodes[y][x].links.push_back(&nodes[y][x-1]);
                nodes[y][x].pos[0] = '<';
            }
            if (height + 1 >= up) {
                nodes[y][x].links.push_back(&nodes[y-1][x]);
                nodes[y][x].pos[1] = '^';
            }
            if (height + 1 >= right) {
                nodes[y][x].links.push_back(&nodes[y][x+1]);
                nodes[y][x].pos[2] = '>';
            }
            if (height + 1 >= down) {
                nodes[y][x].links.push_back(&nodes[y+1][x]);
                nodes[y][x].pos[3] = 'v';
            }
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (start == &nodes[i][j]) {
                std::cout << (char) (nodes[i][j].height - 0x20);
            } else if (end == &nodes[i][j]) {
                std::cout << (char) (nodes[i][j].height - 0x20);
            } else {
                std::cout << nodes[i][j].height;
            }
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (start == &nodes[i][j]) {
                std::cout << 'S';
            } else if (end == &nodes[i][j]) {
                std::cout << 'E';
            } else {
                std::cout << nodes[i][j].links.size();
            }
        }
        std::cout << std::endl;
    }

    for (int y = 0; y < height; y++) {
        for (int k = 0; k < 3; k++) {
            for (int x = 0; x < width; x++) {
                if (start == &nodes[y][x]) {
                    if (k == 0) {
                        std::cout << ' ' << nodes[y][x].pos[1] << ' ';
                    } else if (k == 1) {
                        std::cout << nodes[y][x].pos[0] << nodes[y][x].height << nodes[y][x].pos[2];
                    } else {
                        std::cout << ' ' << nodes[y][x].pos[3] << ' ';
                    }
                } else if (end == &nodes[y][x]) {
                    if (k == 0) {
                        std::cout << ' ' << nodes[y][x].pos[1] << ' ';
                    } else if (k == 1) {
                        std::cout << nodes[y][x].pos[0] << nodes[y][x].height << nodes[y][x].pos[2];
                    } else {
                        std::cout << ' ' << nodes[y][x].pos[3] << ' ';
                    }
                } else {
                    if (k == 0) {
                        std::cout << ' ' << nodes[y][x].pos[1] << ' ';
                    } else if (k == 1) {
                        std::cout << nodes[y][x].pos[0] << nodes[y][x].height << nodes[y][x].pos[2];
                    } else {
                        std::cout << ' ' << nodes[y][x].pos[3] << ' ';
                    }
                }
            }
            std::cout << std::endl;
        }
    }

    node* currentNode = start;
    std::set<node*> visited;
    std::set<node*> notVisited;
    while (visited.find(end) == visited.end()) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                std::cout << (char) (nodes[i][j].tentativeDistance + 0x30);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << "Current node: " << currentNode->xpos << ", " << currentNode->ypos << std::endl;
        if (visited.find(currentNode) != visited.end()) {
            throw "Node already visited!";
        }
        for (node* link : currentNode->links) {
            if (visited.find(link) == visited.end()) {
                int nextDistance = currentNode->tentativeDistance + 1;
                if (nextDistance < link->tentativeDistance) {
                    link->tentativeDistance = nextDistance;
                }
                notVisited.insert(link);
            }
        }
        visited.insert(currentNode);
        notVisited.erase(currentNode);

        auto a = std::min_element(notVisited.begin(), notVisited.end(), [] (node* first, node* second) -> bool {
            return first->tentativeDistance < second->tentativeDistance;
        });

        auto b = *a;
        currentNode = b;
    }

    std::cout << "Shortest path to endpoint is: " << end->tentativeDistance << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
