#include <iostream>
#include <set>

int main()
{
	std::string 		line;
	std::set<int>		sums;
	int					calories = 0;

	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			sums.emplace(calories);
			calories = 0;
		} else {
			calories += atoi(line.c_str());
		}
	}
	std::cout << *sums.rbegin() << std::endl;
	return 0;
}