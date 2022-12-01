#include <help.hpp>
#include <algorithm>

class elf {
private:
    int id;
    int calories;

public:
    elf(int id) : id(id), calories(0) {
    }

    elf& operator+= (int const& calories) {
        this->calories += calories;
        return *this;
    }

    bool operator< (elf const& other) const {
        return this->calories < other.calories;
    }

    bool operator> (elf const& other) const {
        return this->calories > other.calories;
    }

    int getId() {
        return this->id;
    }

    int getCalories() {
        return this->calories;
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    int it = 0;
    std::vector<elf> elfs = {elf(it)};

    for (auto i = lines.begin(); i != lines.end(); i++) {
        try {
            int calories = std::stoi(*i);
            elfs.back() += calories;
        } catch (std::invalid_argument& e) {
            elfs.push_back(elf(++it));
        }
    }

    auto i = std::max_element(elfs.begin(), elfs.end());

    std::cout << "Elf " << i->getId() << " is carrying " << i->getCalories() << " calories." << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
