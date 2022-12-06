#include <iostream>
#include <fstream>

int main() {
    std::ifstream	input("input.txt");
    int             seen[26] = {0};
    int             i = 0;
    int             turnUntilUnique = 14;

    while (i <= turnUntilUnique && input.peek() != '\n') {
        uint8_t index = input.get() - 'a';
        if (seen[index] && (i - seen[index] < 14))
            turnUntilUnique = std::max(turnUntilUnique, seen[index] + 14);
        seen[index] = i++;
    }
    std::cout << i;
    return 0;
}