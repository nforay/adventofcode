#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

struct Folder
{
    Folder*                                     parent;
    std::unordered_map<std::string, Folder*>    folders;
    uint64_t                                    size = 0UL;
    Folder(Folder* dir) : parent(dir) {}
    ~Folder() {
        for (auto &dir : folders)
            delete dir.second;
    }
    uint64_t calcSize() {
        uint64_t total = 0UL;
        for (auto &dir : folders)
            total += dir.second->calcSize();
        if (size <= 10000UL)
            total += size;
        return total;
    }
    void addSize(uint64_t size)
    {
        this->size += size;
        if (parent)
            parent->addSize(size);
    }
};

int     main() {
    std::ifstream   input("input.txt");
    std::string     line;
    Folder          *root = new Folder{NULL};
    Folder          *cwd = root;

    getline(input, line);
    while (getline(input, line)) {
        if (line[0] == '$') {
            if (line[2] == 'c') {
                if (line[5] == '.')
                    cwd = cwd->parent;
                else
                    cwd = cwd->folders[line.substr(5)];
            } else {
                while (input.peek() != '$' && getline(input, line)) {
                    if (isdigit(line[0]))
                        cwd->addSize(strtoul(line.c_str(), NULL, 10));
                    else
                        cwd->folders.emplace(line.substr(4), new Folder{cwd});
                }
            }
        }
    }
    std::cout << root->calcSize();
    delete root;
    return 0;
}