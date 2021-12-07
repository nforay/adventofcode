#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int main()
{
	std::string			line;
	std::vector<int>	crabs;
	int					cost = INT32_MAX;

	while (std::getline(std::cin, line, ','))
		crabs.push_back(atoi(line.c_str()));
	std::sort(crabs.begin(), crabs.end());
	for (int position = crabs.front(); position < crabs.back(); position++) {
		int sum_delta = 0;
		for (auto &dcrab : crabs) {
			int dist = std::abs(position - dcrab);
			sum_delta += (dist + 1) * dist / 2;
		}
		cost = std::min(sum_delta, cost);
	}
	std::cout << "Answer: " << cost << std::endl;
	return (0);
}