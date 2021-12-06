#include <iostream>
#include <vector>
#include <numeric>
#include <sstream>

int main()
{
	std::string				line;
	std::vector<long>		fishes(9, 0l); // Storing how many fishes have said age now
	long					total = 0l;

	std::cin >> line; std::cin.ignore();
	std::istringstream		ss(line);

	while (std::getline(ss, line, ','))
	{
		std::istringstream	ss(line);
		long				age = 0l;
		while (ss >> age)
			fishes[age]++;
	}
	for (int day = 0; day < 256; day++) {
		for (int i = 0; i < 8; i++)
			std::swap(fishes[i], fishes[i + 1]);
		fishes[6] += fishes[8];
		std::cout << "Day " << day << ": " << std::accumulate(fishes.begin(), fishes.end(), total) << " fishes\n";
	}
	std::cout << "Answer: " << std::accumulate(fishes.begin(), fishes.end(), total) << std::endl;
	return (0);
}