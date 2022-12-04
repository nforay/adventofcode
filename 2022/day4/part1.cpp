// -std=c++20
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

int main() {
    std::string             line;
    std::ifstream           input("input.txt");
	int						total = 0;

    while (getline(input, line)) {
		std::bitset<99>	first, second;
		int FE = atoi(line.data() + line.find('-') + 1);
		int SE = atoi(line.data() + line.find_last_of('-') + 1);
		for (int i = stoi(line) - 1; i < FE; i++)
			first.set(i, true);
		for (int i = std::atoi(line.data() + line.find(',') + 1) - 1; i < SE; i++)
			second.set(i, true);
    	if (((first & second) == first) || ((first & second) == second))
			total++;
    }
	std::cout << total;
    return 0;
}