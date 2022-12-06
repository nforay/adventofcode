#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

int main() {
    std::ifstream               input("input.txt");
    unsigned int                seen[26] = {0};
    unsigned int                i = 0;
    unsigned int                turnUntilUnique = 14;

    std::fill(seen, seen + 26, 0);
    while (input.peek() != '\n') {
        uint8_t index = input.get() - 'a';
        if (seen[index] && (i - seen[index] < 14))
            turnUntilUnique = std::max(turnUntilUnique, seen[index] + 14);
        seen[index] = i;
        if (i++ == turnUntilUnique)
            break;
    }
    std::cout << i;
    return 0;
}