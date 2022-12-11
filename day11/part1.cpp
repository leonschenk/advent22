#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <functional>

struct Monkey {
    int id;
    int inspectations = 0;
    std::deque<int> queue;
    std::function<int(int)> operation;
    std::function<int(int)> test;
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::vector<Monkey> monkeys;

    Monkey monkey;
    for (auto line = lines.begin(); line != lines.end(); line++) {
        std::stringstream str = std::stringstream(*line);
        std::string word;
        str >> word;
        if (word == "Monkey") {
            str >> monkey.id;
            std::cout << "Monkey " << monkey.id << ":" << std::endl;
        } else if (word == "Starting") {
            monkey.queue = std::deque<int>();
            while (str >> word) {
                int a;
                str >> a;
                monkey.queue.push_back(a);
            }
            std::cout << "  Starting items: ";
            for (auto& i : monkey.queue) {
                std::cout << i << ",";
            }
            std::cout << std::endl;
        } else if (word == "Operation:") {
            char operation;
            std::string value;
            str >> word >> word >> word >> operation >> value;
            bool oldModifier = value == "old";
            int other = oldModifier ? -1 : std::stoi(value);
            monkey.operation = [operation, oldModifier, other](int old) -> int {
                if (operation == '+') {
                    return old + (oldModifier ? old : other);
                } else if (operation == '*') {
                    return old * (oldModifier ? old : other);
                } else {
                    throw "Niet goed!";
                }
            };
            std::cout << "  Operation: new = old " << operation << " " << (oldModifier ? "old" : "") << other << std::endl;
        } else if (word == "Test:") {
            int a, b, c;
            str >> word >> word >> a;
            line++;
            str = std::stringstream(*line);
            str >> word >> word >> word >> word >> word >> b;
            line++;
            str = std::stringstream(*line);
            str >> word >> word >> word >> word >> word >> c;
            monkey.test = [a, b, c](int level) -> int {
                if (!(level%a)) {
                    return b;
                } else {
                    return c;
                }
            };
            monkeys.push_back(monkey);
            std::cout << "  Test: divisible by " << a << std::endl;
            std::cout << "    If true: throw to monkey " << b << std::endl;
            std::cout << "    If false: throw to monkey " << c << std::endl;
        }
    }

    // rounds
    for (int j = 0; j < 20; j++) {
        for (Monkey& i : monkeys) {
            std::cout << "Monkey " << i.id << std::endl;
            while (!i.queue.empty()) {
                i.inspectations++;
                int current = i.queue.front();
                std::cout << "  Monkey inspects an item with a worry level of " << current << std::endl;
                int newLevel = i.operation(current);
                std::cout << "    Worry level is changed to " << newLevel << std::endl;
                int loweredLevel = newLevel / 3;
                std::cout << "    Worry level is divided by 3 " << loweredLevel << std::endl;
                int throwTo = i.test(loweredLevel);
                std::cout << "    Item with worry level " << loweredLevel << " is throw to monkey " << throwTo << std::endl;

                i.queue.pop_front();
                monkeys[throwTo].queue.push_back(loweredLevel);
            }
        };
    }

    for (Monkey& i : monkeys) {
        std::cout << "Monkey " << i.id << ": ";
        std::cout << "inspected items " << i.inspectations << " times. ";
        for (auto& j : i.queue) {
            std::cout << j << ", ";
        }
        std::cout << std::endl;
    }

    std::sort(monkeys.begin(), monkeys.end(), [] (const Monkey& a, const Monkey& b) -> bool {
        return a.inspectations > b.inspectations;
    });

    std::cout << "Total score: " << (monkeys[0].inspectations * monkeys[1].inspectations) << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
