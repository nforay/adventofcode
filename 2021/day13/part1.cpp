#include <iostream>
#include <vector>
#include <list>
#include <sstream>

void fold_paper(std::vector<std::string> &paper, const std::pair<char, int> &fold) {
	switch (fold.first) {
		case 'x':
			for (auto &line : paper) {
				std::string::iterator it = line.begin();
				for (int i = fold.second; i > 0; i--, it++) {
					*it = (*it == '#' ? *it : line.back());
					line.pop_back();
				}
				line.pop_back();
			}
			break;
		case 'y':
			std::vector<std::string>::iterator itvf = paper.begin();
			while (paper.size() - 1 > fold.second) {
				std::string::iterator itf = (*itvf).begin();
				for (std::string::iterator itb = paper.back().begin(); itb != paper.back().end(); itb++, itf++) {
					*itf = (*itf == '#' ? *itf : *itb);
				}
				paper.pop_back();
				itvf++;
			}
			paper.pop_back();
			break;
	}
}

int main()
{
	std::list<std::pair<int, int>> 			dots;
	std::list<std::pair<char, int>>			folds;
	std::vector<std::string>				paper;
	std::string								line;
	int										total = 0;
	int										width = 0;
	int										height = 0;

	while (std::getline(std::cin, line)) {
		if (!line.size())
			break;
		std::stringstream	ss;
		ss.str(line);
		std::pair<int, int> dot;
		ss >> dot.first; ss.ignore();
		ss >> dot.second;
		dots.push_back(dot);
	}
	while (std::getline(std::cin, line)) {
		std::pair<char, int> fold;
		fold.first = line[11];
		fold.second = std::stoi(line.c_str() + 13);
		folds.push_back(fold);
	}
	for (auto &dot : dots) {
		width = std::max(width, dot.first);
		height = std::max(height, dot.second);
	}
	paper.resize(height + 1, std::string(width + 1, '.'));
	for (auto &dot : dots)
		paper[dot.second][dot.first] = '#';
	fold_paper(paper, folds.front());
	for (auto &line : paper)
		total += count(line.begin(),line.end(), '#');
	std::cout << "Total: " << total << std::endl;
	return (0);
}