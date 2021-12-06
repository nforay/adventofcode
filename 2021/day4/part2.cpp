#include <iostream>
#include <vector>
#include <sstream>

int main()
{
	std::string						line;
	std::vector<bool>				drawn(100, false);
	std::vector<int>				grids;
	int								draw;
	int								winner = 0;
	int  							score = 0;

	grids.reserve(100*5*5); //100 grids in the input, avoiding 13 resizes with a growth factor of 2;
	std::cin >> line; std::cin.ignore();
	std::istringstream				ss(line);
	while (std::cin >> line)
	{
		std::istringstream	ss(line);
		int					num = 0;
		while (ss >> num)
			grids.push_back(num);
	}
	std::cerr << "Draw: ";
	while (std::getline(ss, line, ','))
	{
		draw = std::stoi(line);
		drawn[draw] = true;
		for (auto it = grids.begin(); it != grids.end() && grids.size();) {
			int i = it - grids.begin();
			for (auto j : {0, 1, 2, 3, 4}) {
				if ((drawn[grids[i+j*5]] & 1 & drawn[grids[i+j*5+1]] & drawn[grids[i+j*5+2]] & drawn[grids[i+j*5+3]] & drawn[grids[i+j*5+4]]) ||
					(drawn[grids[i+j]] & 1 & drawn[grids[i+j+1*5]] & drawn[grids[i+j+2*5]] & drawn[grids[i+j+3*5]] & drawn[grids[i+j+4*5]]))
				{
					std::cerr << "New winning board:\n";
					winner = i;
					score = 0;
					for (auto i : {0, 1, 2, 3, 4}) {
						for (auto j : {0, 1, 2, 3, 4}) {
							std::cerr << (drawn[grids[winner + i*5 + j]] ? "\e[31m" : "") << grids[winner + i*5 + j] << (drawn[grids[winner + i*5 + j]] ? "\e[0m\t" : "\t");
							if (!drawn[grids[winner + i*5 + j]])
								score += grids[winner + i*5 + j];
						}
						std::cerr << "\n";
					}
					std::cerr << "Sum of unmarked numbers: " << score;
					score *= draw;
					std::cerr << " score: " << score << "\n";
					it = grids.erase(it, it + 25);
					break;
				}
				if (j == 4)
					it += 25;
			}
		}
	}
	std::cout << "Answer: " << score << std::endl;
	return (0);
}