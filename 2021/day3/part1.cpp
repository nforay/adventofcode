#include <iostream>
#include <vector>
#include <bitset>

int main()
{
	std::string					line;
	std::vector<int>			lines;
	int							gamma = 0;
	int							epsilon = 0;
	while (std::cin >> line)
		lines.push_back(std::bitset<12>(line).to_ulong());
	for (auto i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11})
	{
		int count = 0;
		for (auto &line : lines)
			if (line & (1 << i))
				count++;
		if (count > lines.size()/2)
			gamma |= 1 << i;
		else
			epsilon |= 1 << i;
	}
	std::cerr << "Gamma: " << gamma << std::endl;
	std::cerr << "Epsilon: " << epsilon << std::endl;
	std::cout << "Answer: " << gamma * epsilon << std::endl;
	return (0);
}