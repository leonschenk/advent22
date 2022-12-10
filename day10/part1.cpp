#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <set>
#include <functional>

inline bool print(bool* screen, int cycle, long pos) {
    if ((cycle%40) >= pos-1 && (cycle%40) <= pos+1) {
        screen[cycle] = true;
        return true;
    } else {
        screen[cycle] = false;
        return true;
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    long registerX = 1;
    long cycle = 0;
    bool busy = false, nextBusy = false;
    int toAdd = 0;

    bool screen[6][40];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            screen[i][j] = false;
        }
    }

    for (int j = 0; j < 40; j++) {
        bool isSprite = (j >= ((registerX%40) - 1)) && (j <= ((registerX%40) + 1));
        std::cout << (isSprite ? 'x' : '.');
    }
    std::cout << std::endl << std::endl;

    std::vector<std::string>::iterator line = lines.begin();
    while (line != lines.end()) {
        if (!busy) {
            std::cout << "begin executing " << *line << std::endl;
            if ((*line)[0] == 'a') {
                nextBusy = true;
                toAdd = std::stoi((*line).substr(5));
            } else if ((*line)[0] == 'n') {
                nextBusy = false;
            }
            line++;
        }

        // draw current position
        if (print(&screen[0][0], cycle, registerX)) {
            std::cout << "CRT draws pixel in position " << cycle << std::endl;
        }

        std::cout << "Current CRT row: ";
        for (int j = 0; j < 40; j++) {
            std::cout << (char) (screen[cycle/40][j] ? 'x' : '.');
        }
        std::cout << std::endl;

        if (busy) {
            registerX += toAdd;
            std::cout << "finish executing addx " << toAdd << " (Register X is now " << registerX << ")" << std::endl;
            for (int j = 0; j < 40; j++) {
                bool isSprite = (j >= ((registerX%40) - 1)) && (j <= ((registerX%40) + 1));
                std::cout << (isSprite ? 'x' : '.');
            }
            std::cout << std::endl;
        }
        busy = nextBusy;
        nextBusy = false;
        cycle++;
        std::cout << std::endl;
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 40; j++) {
            std::cout << (screen[i][j] ? 'x' : '.');
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << std::endl;
}
