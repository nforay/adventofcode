#include <iostream>
#include <vector>

#define WIDTH 100
#define HEIGHT 100

int main()
{
	std::string			line;
	std::vector<char>	heightmap;
	int					total = 0;

	heightmap.reserve(HEIGHT * WIDTH);
	while (std::getline(std::cin, line))
		for (auto &c : line)
			heightmap.push_back(c);
	for (int i = 0; i < heightmap.size(); i++)
	{
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
		total += (heightmap[i] - '0') + 1;
	}
	std::cout << "Answer: " << total << std::endl;
	return (0);
}