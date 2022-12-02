#include <help.hpp>
#include <algorithm>

enum class RockPaperScissors : int {
    ROCK = 0,
    PAPER = 1,
    SCISSORS = 2
};

const int win = 6;
const int lose = 0;
const int draw = 3;

const int rock = 1;
const int paper = 2;
const int scissors = 3;

int scoresMatrix[3][3] = {
    {rock + draw, paper + win , scissors + lose },
    {rock + lose, paper + draw, scissors + win  },
    {rock + win , paper + lose, scissors + draw }
};

RockPaperScissors fromInput(char input) {
    switch (input) {
        case 'A':
        case 'X':
            return RockPaperScissors::ROCK;
        case 'B':
        case 'Y':
            return RockPaperScissors::PAPER;
        case 'C':
        case 'Z':
            return RockPaperScissors::SCISSORS;
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

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    int totalScore = 0;
    for (auto i = lines.begin(); i != lines.end(); i++) {
        RockPaperScissors othersChoice = fromInput((*i)[0]);
        RockPaperScissors yourChoice = fromInput((*i)[2]);

        std::cout << "other chooses " << othersChoice << ", you should choose " << yourChoice << std::endl;
        std::cout << "outcome: " << scoresMatrix[(int) othersChoice][(int) yourChoice] << std::endl;
        totalScore += scoresMatrix[(int) othersChoice][(int) yourChoice];
    }

    std::cout << "Total score is of the match is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
