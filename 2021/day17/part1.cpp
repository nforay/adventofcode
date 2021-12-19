#include <iostream>
#include <regex>

typedef struct coord {
	int x;
	int y;
} coord;

bool ontarget(const coord &pos, const coord &start, const coord &end) {
	return ((start.x <= pos.x && pos.x <= end.x) && (end.y <= pos.y && pos.y <= start.y));
}

bool launchprobe(coord vel, int &maxy, const coord &start, const coord &end)
{
	coord pos = {0, 0};
	int height = 0;
	while (!ontarget(pos, start, end) && pos.x <= end.x && pos.y >= end.y) {
		pos.x += vel.x;
		pos.y += vel.y;
		height = std::max(height, pos.y);
		vel.x = (vel.x < 0 ? vel.x + 1 : vel.x > 0 ? vel.x - 1 : vel.x);
		vel.y--;
	}
	if (ontarget(pos, start, end))
		maxy = std::max(maxy, height);
	return (ontarget(pos, start, end));
}

int main()
{
	std::string		str;
	coord			start, end;
	std::regex		values_regex("^target area: x=(-?\\d+)..(-?\\d+), y=(-?\\d+)..(-?\\d+)$");
	std::smatch		matches;
	int				maxy;

	while (std::getline(std::cin, str)) {
		if(std::regex_search(str, matches, values_regex)) {
			maxy = 0;
			start.x = stoi(matches[1].str());
			end.x = stoi(matches[2].str());
			start.y = stoi(matches[4].str());	// swap y so that min is top left corner
			end.y = stoi(matches[3].str());		// max is bottom right corner
			std::cerr << "min/max X: " << start.x << "," << end.x << " Y: " << start.y << "," << end.y << std::endl;
			for (int x = 0; x <= end.x;  x++)
				for (int y = 0; y < std::max(abs(end.y), maxy); y++)
					if (launchprobe({x, y}, maxy, start, end))
						std::cerr << "Hit with velocity " << x << "," << y << " Max y:" << maxy << std::endl;
		}
	}
	std::cout << "Answer: " << maxy << std::endl;
	return (0);
}