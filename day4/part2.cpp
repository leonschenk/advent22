#include <help.hpp>
#include <algorithm>
#include <sstream>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    int totalScore = 0;
    for (auto &i : lines) {
        std::stringstream str = std::stringstream(i);

        int from1, to1, from2, to2;
        char dash, comma;

        str >> from1 >> dash >> to1 >> comma >> from2 >> dash >> to2;

        int a = from1 - to2;
        int b = to1 - from2;
        if (a * b <= 0) {
            totalScore++;
            std::cout << "score! ";
        }

        std::cout << from1 << '-' << to1 << ',' << from2 << '-' << to2 << std::endl;
    }

    std::cout << "Total score is of the match is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
