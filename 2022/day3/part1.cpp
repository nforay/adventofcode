// -std=c++20
#include <iostream>
#include <fstream>
#include <string_view>
#include <bitset>

//        27         ->           52      1           ->          26
//        22233333333334444444444555______00000000011111111112222222
//        78901234567890123456789012______12345678901234567890123456
//mask : "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz"

int main() {
	std::string 		line;
	std::ifstream		input("input.txt");
	std::bitset<59>		maskA, maskB, duplicates;
	int					sum = 0;

	for (; input.good() && getline(input, line);) {
		std::string_view	svA(line.begin(), line.begin() + line.size() / 2);
		std::string_view	svB(line.begin() + line.size() / 2, line.end());
		maskA.reset();
		maskB.reset();
		duplicates.reset();
		for (int i = 0; i < svA.size(); i++) {
			maskA.set(svA[i] - 'A', true);
			maskB.set(svB[i] - 'A', true);
		}
		duplicates = (maskA & maskB);
		for (int i = 0; i < 59; i++) {
			if (duplicates[i])
				sum += (i < 26 ? i + 27 : i - 31);
		}
	}
	input.close();
	std::cout << sum << "\n";
	return 0;
}