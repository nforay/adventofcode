#include <iostream>
#include <vector>
#include <map>

int main()
{
	std::string							line;
	std::vector<int>					crabs;
	std::map<int, bool>					tested;
	std::pair<int, int>					best_position(std::make_pair(INT32_MAX, 0));
	int									cost = 0;

	while (std::getline(std::cin, line, ','))
		crabs.push_back(atoi(line.c_str()));
	for (auto &crab : crabs) {
		if (tested[crab])
			continue;
		tested[crab] = true;
		int sum_delta = 0;
		for (auto &dcrab : crabs)
			sum_delta += std::abs(crab - dcrab);
		std::cerr << "Position: " << crab << " cost: " << sum_delta << std::endl;
		if (sum_delta < best_position.first)
			best_position = std::make_pair(sum_delta, crab);
	}
	std::cerr << "Best position is " << best_position.second << std::endl;
	for (auto &crab : crabs)
		cost += std::abs(crab - best_position.second);
	std::cout << "Answer: " << cost << std::endl;
	return (0);
}