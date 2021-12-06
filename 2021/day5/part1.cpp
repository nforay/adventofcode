#include <iostream>
#include <vector>
#include <algorithm>
#include <regex>

int main()
{
	std::string					line;
	std::vector<int>			diagram(1000*1000, 0);
	std::regex					values_regex("^(\\d+),(\\d+) -> (\\d+),(\\d+)$");
	std::smatch					matches;
	int							startx, starty, endx, endy;

	while (getline(std::cin, line)) {
		if(std::regex_search(line, matches, values_regex)) {
			startx = stoi(matches[1].str());
			starty = stoi(matches[2].str());
			endx = stoi(matches[3].str());
			endy = stoi(matches[4].str());
			if (startx != endx && starty != endy) //ignore diagonals
				continue;
			for (int i = abs(startx - endx + starty - endy); i >= 0; i--)
				diagram[((startx != endx ? (startx > endx ? startx - i : startx + i) : endx) + ((starty != endy ? (starty > endy ? starty - i : starty + i) : endy)) * 1000)]++;
		}
	}
	std::cout << "Answer: " << std::count_if(diagram.begin(), diagram.end(), [](int value){ return (value > 1); }) << std::endl;
	return (0);
}