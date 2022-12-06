#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    for (auto& j : lines) {
        const char* buffer = j.c_str();
        for (int i = 3; i < j.length();) {
            if (buffer[i] == buffer[i-1]) {
                i += 3;
            } else if (buffer[i] == buffer[i-2]) {
                i += 2;
            } else if (buffer[i-1] == buffer[i-2]) {
                i += 2;
            } else if (buffer[i] == buffer[i-3]) {
                i += 1;
            } else if (buffer[i-1] == buffer[i-3]) {
                i += 1;
            } else if (buffer[i-2] == buffer[i-3]) {
                i += 1;
            } else {
                std::cout << " First start of packet is: " << (i + 1) << std::endl;
                break;
            }
        }
    }

    std::cout << std::endl << std::endl << std::endl;
}
