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
    for (auto &i : lines) {
        bool contained[256];
        std::fill(contained, contained + 256, false);
        int j = 0;
        for (; j < (i.length() >> 1); j++) {
            contained[i[j]] = true;
            std::cout << i[j];
        }
        std::cout << std::endl;
        for (; j < i.length(); j++) {
            if (contained[i[j]]) {
                totalScore += priorities[i[j]];
                std::cout << "Found " << i[j] << priorities[i[j]] << std::endl;
            }
            contained[i[j]] = false;
        }
        std::cout << std::endl;
    }

    std::cout << "Total score is of the match is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
