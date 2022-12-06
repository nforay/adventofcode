#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream               input("input.txt");
    char                        seen[4] = {0, 0, 0, 0};
    unsigned int                i = 0;

    while (input.peek() != '\n') {
        seen[i++ % 4] = input.get();
        if (i > 3 && (seen[0] != seen[1] && seen[1] != seen[2] &&
                seen[2] != seen[3] && seen[3] != seen[0] &&
                seen[1] != seen[3] && seen[0] != seen[2]))
            break;
    }
    std::cout << i;
    return 0;
}