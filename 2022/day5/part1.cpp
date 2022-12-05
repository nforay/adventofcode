// -std=c++20
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>

int main() {
    std::string                 line;
    std::ifstream               input("input.txt");
    std::vector<std::string>    rows;
    std::stack<char>            supplies[10];

    while (getline(input, line) && !line.empty()) {
        rows.push_back(line);
    }
    for (auto it = ++rows.rbegin(); it != rows.rend(); it++) {
        for (int i = 1; i < 35; i += 4) {
            if (isalpha((*it)[i]))
                supplies[i / 4 + 1].push((*it)[i]);
        }
    }
    while (getline(input, line)) {
        std::istringstream iss(line);
        int move, from, to;
        iss >> line >> move >> line >> from >> line >> to;
        while (move--) {
            supplies[to].push(supplies[from].top());
            supplies[from].pop();
        }
    }
    for (int i = 1; i < 10; i++)
        std::cout << supplies[i].top();
    return 0;
}