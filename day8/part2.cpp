#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <functional>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    long totalScore = 0;

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].length(); j++) {
            char height = lines[i][j];

            long scoreTop = 0;
            for (int k = i - 1; k >= 0; k--) {
                scoreTop++;
                if (lines[k][j] >= height) {
                    break;
                }
            }
            long scoreLeft = 0;
            for (int k = j - 1; k >= 0; k--) {
                scoreLeft++;
                if (lines[i][k] >= height) {
                    break;
                }
            }
            long scoreRight = 0;
            for (int k = j + 1; k < lines[i].length(); k++) {
                scoreRight++;
                if (lines[i][k] >= height) {
                    break;
                }
            }
            long scoreBottom = 0;
            for (int k = i + 1; k < lines.size(); k++) {
                scoreBottom++;
                if (lines[k][j] >= height) {
                    break;
                }
            }
            long score = scoreLeft * scoreTop * scoreRight * scoreBottom;
            if (score > totalScore) {
                totalScore = score;
            }
            std::cout << scoreTop;
        }
        std::cout << std::endl;
    }

    std::cout << "Total score is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
