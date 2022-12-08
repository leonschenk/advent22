#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <functional>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    int totalScore = 0;

    char maxLeft;
    int scoreLeft;
    char *maxTop = new char[lines[0].length()];
    for (int i = 0; i < lines[0].length(); i++) {
        maxTop[i] = 0;
    }
    for (int i = 0; i < lines.size(); i++) {
        maxLeft = 0;
        for (int j = 0; j < lines[i].length(); j++) {
            char height = lines[i][j];
            char toAdd = 0;
            if (maxTop[j] < height) {
                // visible from top
                maxTop[j] = height;
                toAdd = 't';
            }
            if (maxLeft < height) {
                // visible from left
                maxLeft = height;
                toAdd = 'l';
            }
            if (!toAdd) {
                // visible from right
                toAdd = 'r';
                for (int k = j + 1; k < lines[i].length(); k++) {
                    if (lines[i][k] >= height) {
                        // not visible from right
                        toAdd = 0;
                        break;
                    }
                }
            }
            if (!toAdd) {
                // visible from bottom
                toAdd = 'b';
                for (int k = i + 1; k < lines.size(); k++) {
                    if (lines[k][j] >= height) {
                        // not visible from bottom
                        toAdd = 0;
                        break;
                    }
                }
            }
            if (toAdd) {
                totalScore++;
                std::cout << toAdd;
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
    delete[] maxTop;

    std::cout << "Total score is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
