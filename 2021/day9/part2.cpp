#include <iostream>
#include <vector>
#include <set>

#define WIDTH 100
#define HEIGHT 100

void	flood_fill(std::vector<char> &heightmap, int pos, int &count)
{
	count++;
	heightmap[pos] = 'F';
	if (pos > WIDTH && heightmap[pos-WIDTH] < '9')
		flood_fill(heightmap, pos-WIDTH, count);
	if (pos < WIDTH*(HEIGHT-1) && heightmap[pos+WIDTH] < '9')
		flood_fill(heightmap, pos+WIDTH, count);
	if (pos % WIDTH && heightmap[pos-1] < '9')
		flood_fill(heightmap, pos-1, count);
	if ((pos % WIDTH) < (WIDTH-1) && heightmap[pos+1] < '9')
		flood_fill(heightmap, pos+1, count);
}

int 	main()
{
	std::string			line;
	std::vector<char>	heightmap;
	std::vector<int>	lowpoints;
	std::set<int>		bassins;
	int					total = 1;

	heightmap.reserve(HEIGHT * WIDTH);
	while (std::getline(std::cin, line))
		for (auto &c : line)
			heightmap.push_back(c);
	for (int i = 0; i < heightmap.size(); i++) {
		if (heightmap[i] == '9')
			continue;
		if (i > WIDTH && heightmap[i-WIDTH] < heightmap[i])
			continue;
		if (i < WIDTH*(HEIGHT-1) && heightmap[i+WIDTH] < heightmap[i])
			continue;
		if (i % WIDTH && heightmap[i-1] < heightmap[i])
			continue;
		if ((i % WIDTH) < (WIDTH-1) && heightmap[i+1] < heightmap[i])
			continue;
			lowpoints.push_back(i);
	}
	for (auto &i : lowpoints) {
		int tmp = 0;
		flood_fill(heightmap, i, tmp);
		if (bassins.size() < 3 || tmp > *bassins.begin())
			bassins.insert(tmp);
		if (bassins.size() > 3)
			bassins.erase(bassins.begin());
	}
	for (auto &bassin : bassins)
		total *= bassin;
	std::cout << "Answer: " << total << std::endl;
	return (0);
}