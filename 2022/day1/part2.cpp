#include <iostream>
#include <set>
#include <numeric>

int main()
{
	std::string 							line;
	std::multiset<int, std::greater<int>>	sums;
	int										calories = 0;

	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			sums.emplace(calories);
			calories = 0;
		} else {
			calories += atoi(line.c_str());
		}
	}
	std::cout << std::accumulate(sums.begin(), next(sums.begin(), 3), 0) << std::endl;
	return 0;
}