#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <set>

struct Folder
{
    Folder*                                     parent;
    std::unordered_map<std::string, Folder*>    folders;
    uint64_t                                    size = 0;
    Folder(Folder* dir) : parent(dir) {}
    ~Folder() {
        for (auto &dir : folders)
            delete dir.second;
    }
    void findBestCandidate(std::set<uint64_t> &directories, uint64_t required) {
        for (auto &dir : folders)
            dir.second->findBestCandidate(directories, required);
        if (size >= required)
            directories.insert(size);
    }
    void addSize(uint64_t size)
    {
        this->size += size;
        if (parent)
            parent->addSize(size);
    }
};

int     main() {
    std::ifstream       input("input.txt");
    std::string         line;
    Folder              *root = new Folder{NULL};
    Folder              *cwd = root;
    uint64_t            smallest = UINT64_MAX;
    std::set<uint64_t>  directories;

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
    root->findBestCandidate(directories, 30000000 - (70000000 - root->size));
    std::cout << *directories.begin();
    delete root;
    return 0;
}
