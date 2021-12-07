#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

int main()
{
	std::string							line;
	std::vector<int>					crabs;
	std::pair<int, int>					best_position(std::make_pair(INT32_MAX, 0));
	int									cost = INT32_MAX;

	std::cin >> line; std::cin.ignore();
	std::istringstream		ss(line);

	while (std::getline(ss, line, ','))
	{
		std::istringstream	sspos(line);
		int					pos = 0;
		while (sspos >> pos)
			crabs.push_back(pos);
	}
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