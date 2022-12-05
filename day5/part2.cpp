#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    int count = (lines.begin()->length() + 1) >> 2;
    std::deque<char> *queues = new std::deque<char>[count];

    bool linebreak;
    for (auto &i : lines) {
        if (i.length() < 1) {
        } else if (i.at(0) != 'm') {
            for (int j = 0; j < count; j++) {
                char& blockname = i.at(j*4 + 1);
                if (blockname >= 'A') {
                    queues[j].push_front(blockname);
                }
            }
            // start situation
        } else if (i.at(0) == 'm') {
            std::stringstream str = std::stringstream(i);
            // move instruction
            int c, from, to;
            char padding;
            
            str >> padding >> padding >> padding >> padding >> c;
            str >> padding >> padding >> padding >> padding >> from;
            str >> padding >> padding >> to;

            std::deque<char> todo;

            for (int j = 0; j < c; j++) {
                char a = queues[from-1].back();
                queues[from-1].pop_back();
                todo.push_front(a);
            }
            for (auto& j : todo) {
                queues[to-1].push_back(j);
            }
        }
    }

    std::string totalScore;
    for (int i = 0; i < count; i++) {
        totalScore += queues[i].back();
        std::cout << "Queue: " << (i + 1) << " length: " << queues[i].size() << " queue: " << queues[i].back() << std::endl;
    }

    delete[] queues;

    std::cout << "Total score is of the match is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
