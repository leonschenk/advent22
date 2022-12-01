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

    std::sort(elfs.begin(), elfs.end(), std::greater<elf>());

    int totaal = 0;
    for (int i = 0; i < 3; i++) {
        std::cout << "Elf " << elfs[i].getId() << " is carrying " << elfs[i].getCalories() << " calories." << std::endl;
        totaal += elfs[i].getCalories();
    }
    std::cout << "Total amount of calories carried by the elfs is: " << totaal << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
