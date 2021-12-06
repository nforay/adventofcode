#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>

int main()
{
	std::string					line;
	std::vector<int>			fishes;

	std::cin >> line; std::cin.ignore();
	std::istringstream			ss(line);
	while (std::getline(ss, line, ','))
	{
		std::istringstream	ss(line);
		int					age = 0;
		while (ss >> age)
			fishes.push_back(age);
	}
	std::cerr << "Initial state: ";
	for (auto fish : fishes)
			std::cerr << fish << ",";
		std::cerr << "\b \n";
	for (int day = 1; day < 81; day++) {
		for (int fish = fishes.size() - 1; fish >= 0; fish--) {
			fishes[fish]--;
			if (fishes[fish] < 0) {
				fishes.push_back(8);
				fishes[fish] = 6;
			}
		}
		std::cerr << "after " << day << " days: ";
		for (auto fish : fishes)
			std::cerr << fish << ",";
		std::cerr << "\b \n";
	}
	std::cout << "Answer: " << fishes.size() << std::endl;
	return (0);
}