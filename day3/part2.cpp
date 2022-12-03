#include <help.hpp>
#include <algorithm>

int priorities[256] = {};

int main(int argc, char* argv[]) {
    for (int i = 0; i < 256; i++) {
        if (i >= 'A' && i <= 'Z') {
            priorities[i] = i - 'A' + 27;
        } else if (i >= 'a' && i <= 'z') {
            priorities[i] = i - 'a' + 1;
        }
    }

    std::vector<std::string> lines = readFile(argc, argv);

    int totalScore = 0;
    for (auto i = lines.begin(); i < lines.end();) {
        bool contained[256][3];
        for (int j = 0; j < 256; j++) {
            contained[j][0] = false;
            contained[j][1] = false;
            contained[j][2] = false;
        }
        int j = 0;
        for (int j = 0; j < 3; j++) {
            for (auto& k : (*i)) {
                contained[k][j] = true;
            }
            i++;
        }
        for (int j = 0; j < 256; j++) {
            if (contained[j][0] && contained[j][1] && contained[j][2]) {
                std::cout << "Found: " << (char) j << " score " << priorities[j] << std::endl;
                totalScore += priorities[j];
                break;
            }
        }
    }

    std::cout << "Total score is of the match is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
