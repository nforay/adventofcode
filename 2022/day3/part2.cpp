// -std=c++20
#include <iostream>
#include <fstream>
#include <cmath>
#include <bitset>

//        27         ->           52      1           ->          26
//        22233333333334444444444555______00000000011111111112222222
//        78901234567890123456789012______12345678901234567890123456
//mask : "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz"

int main() {
    std::string 		    line;
    std::ifstream		    input("input.txt");
    long long               mask[3];
    int					    sum = 0;
    static const uint8_t    value[58] = {27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
        37, 38, 39, 40, 41, 42, 43, 44, 45 , 46, 47, 48, 49, 50, 51, 52, 0, 0,
        0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
        18, 19, 20, 21, 22, 23, 24, 25, 26};

    while (input.peek() != EOF) {
        for (int i = 0; i < 3; i++) {
            mask[i] = 0LL;
            getline(input, line);
            for (int j = 0; j < line.size(); j++)
                mask[i] |= 1LL << (line[j] - 'A');
        }
        sum += value[(int)log2(mask[0] & mask[1] & mask[2])];
    }
    std::cout << sum;
    return 0;
}