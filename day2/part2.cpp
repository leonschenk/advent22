#include <help.hpp>
#include <algorithm>

const int rock = 1;
const int paper = 2;
const int scissors = 3;

const int win = 6;
const int lose = 0;
const int draw = 3;

enum class RockPaperScissors : int {
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2
};

int scoresMatrix[3][3] = {
    {win + paper,    draw + rock,     lose + scissors},
    {win + scissors, draw + paper,    lose + rock},
    {win + rock,     draw + scissors, lose + paper}
};

enum class WinDrawLose : int {
    WIN = 0,
    DRAW = 1,
    LOSE = 2
};

RockPaperScissors fromInput(char input) {
    switch (input) {
        case 'A':
            return RockPaperScissors::ROCK;
        case 'B':
            return RockPaperScissors::PAPER;
        case 'C':
            return RockPaperScissors::SCISSORS;
        default:
            throw std::invalid_argument("No input");
    }
}

WinDrawLose fromOther(char input) {
    switch (input) {
        case 'X':
            return WinDrawLose::LOSE; 
        case 'Y':
            return WinDrawLose::DRAW;
        case 'Z':
            return WinDrawLose::WIN;
        default:
            throw std::invalid_argument("No input");
    }
}

std::ostream& operator<< (std::ostream& stream, RockPaperScissors const& output) {
    switch (output) {
        case RockPaperScissors::ROCK:
            stream << "rock";
            break;
        case RockPaperScissors::PAPER:
            stream << "paper";
            break;
        case RockPaperScissors::SCISSORS:
            stream << "scissors";
            break;
    }

    return stream;
}

std::ostream& operator<< (std::ostream& stream, WinDrawLose const& output) {
    switch (output) {
        case WinDrawLose::LOSE:
            stream << "lose";
            break;
        case WinDrawLose::DRAW:
            stream << "draw";
            break;
        case WinDrawLose::WIN:
            stream << "win";
            break;
    }

    return stream;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    int totalScore = 0;
    for (auto i = lines.begin(); i != lines.end(); i++) {
        RockPaperScissors othersChoice = fromInput((*i)[0]);
        WinDrawLose yourChoice = fromOther((*i)[2]);

        std::cout << "other chooses " << othersChoice << ", you should " << yourChoice << std::endl;
        std::cout << "outcome: " << scoresMatrix[(int) othersChoice][(int) yourChoice] << std::endl;
        totalScore += scoresMatrix[(int) othersChoice][(int) yourChoice];
    }

    std::cout << "Total score is of the match is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
