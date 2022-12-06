#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>

const int distinctCharacters = 14;

inline int getStep(const char* buffer) {
    for (int j = 1; j < distinctCharacters; j++) {
        for (int k = 0; k < j; k++) {
            if (buffer[-k] == buffer[-j]) {
                return distinctCharacters - j;
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    for (auto& j : lines) {
        const char* buffer = j.c_str();
        for (int i = distinctCharacters - 1; i < j.length();) {
            int stepCount = getStep(&buffer[i]);
            if (stepCount) {
                i += stepCount;
            } else {
                std::cout << " First start of packet is: " << (i + 1) << std::endl;
                break;
            }
        }
    }

    std::cout << std::endl << std::endl << std::endl;
}
