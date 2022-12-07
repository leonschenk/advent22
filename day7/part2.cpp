#include <help.hpp>
#include <algorithm>
#include <sstream>
#include <deque>
#include <functional>

class Directory {
public:
    Directory(const std::string name, Directory* parent) : name(name), parent(parent), fileSize(0) {
    }

    Directory(const Directory& other) : name(other.name), parent(other.parent), fileSize(other.fileSize) {
    }

    void add(const long fileSize) {
        this->fileSize += fileSize;
        if (parent) {
            parent->add(fileSize);
        }
    }

    void add(const Directory&& dir) {
        subDirectories.push_back(dir);
    }

    const std::string& getName() const  {
        return name;
    }

    Directory* const getParent() const {
        return parent;
    }

    const long getSize() const {
        return fileSize;
    }

    Directory* const getDirectory(const std::string& name) {
        for (std::vector<Directory>::iterator i = subDirectories.begin(); i != subDirectories.end(); i++) {
            if (!name.compare(i->getName())) {
                return &(*i);
            }
        }
        return nullptr;
    }

    void walk(const std::function<bool (const Directory* const dir)>& lambda) const {
        if (lambda.operator()(this)) {
            for (auto& i : this->subDirectories) {
                i.walk(lambda);
            }
        }
    }

private:
    const std::string name;
    Directory* const parent;
    std::vector<Directory> subDirectories;
    long fileSize;
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    const long totalDiskSpace = 70000000;
    const long requiredDiskSpace = 30000000;

    Directory root = Directory("/", nullptr);
    Directory* cwd = &root;
    for (auto& j : lines) {
        if (j[0] == '$' && j[2] == 'c') {
            // change working directory
            if (j[5] == '/') {
                cwd = &root;
            } else if (j[5] == '.') {
                cwd = cwd->getParent();
            } else {
                cwd = cwd->getDirectory(j.substr(5));
                if (!cwd) {
                    throw "niet goed!";
                }
            }
        } else if (j[0] == '$' && j[2] == 'l') {
        } else if (j[0] == 'd') {
            // directory
            cwd->add(Directory(j.substr(4), cwd));
        } else {
            // file
            long size = std::stol(j);
            cwd->add(size);
        }
    }

    const long unUsedSpace = totalDiskSpace - root.getSize();

    std::cout << "Total unused disk space: " << unUsedSpace << std::endl;
    const long requiredFreeUpSpace = requiredDiskSpace - unUsedSpace;
    std::cout << "Required free space: " << requiredFreeUpSpace << std::endl;

    long totalScore = root.getSize();
    root.walk([&totalScore, requiredFreeUpSpace] (const Directory* const cur) -> bool {
        std::cout << "Walking directory: " << cur->getName() << " (" << cur->getSize() << ")" << std::endl;
        if (cur->getSize() > requiredFreeUpSpace) {
            if (cur->getSize() < totalScore) {
                totalScore = cur->getSize();
            }
            return true;
        } else {
            return false;
        }
    });

    std::cout << "Total score is: " << totalScore << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
