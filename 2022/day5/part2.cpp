// -std=c++20
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string                 line;
    std::ifstream               input("input.txt");
    std::vector<std::string>    rows;
    std::vector<char>            supplies[10];

    while (getline(input, line) && !line.empty()) {
        rows.push_back(line);
    }
    for (auto it = ++rows.rbegin(); it != rows.rend(); it++) {
        for (int i = 1; i < 35; i += 4) {
            if (isalpha((*it)[i]))
                supplies[i / 4 + 1].push_back((*it)[i]);
        }
    }
    while (getline(input, line)) {
        std::istringstream iss(line);
        int move, from, to;
        iss >> line >> move >> line >> from >> line >> to;
		supplies[to].insert(supplies[to].end(),
			std::make_move_iterator(supplies[from].end() - move),
			std::make_move_iterator(supplies[from].end()));
		supplies[from].erase(supplies[from].end() - move, supplies[from].end());
    }
    for (int i = 1; i < 10; i++)
        std::cout << supplies[i].back();
    return 0;
}