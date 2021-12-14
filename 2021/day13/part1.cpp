#include <iostream>
#include <vector>
#include <list>
#include <sstream>

void merge_string(auto idst, auto isrc, int len)
{
	while (len--)
		*idst++ = std::max(*idst, *isrc++);
}

void fold_paper(std::vector<std::string> &paper, const char &fold) {
	if (fold == 'x') {
		for (int i = 0; i < paper.size(); ++i) {
			merge_string(paper[i].begin(), paper[i].rbegin(), paper[i].size() / 2);
			paper[i].resize(paper[i].size() / 2);
		}
	} else {
		for (int i = 0; i < paper.size() / 2; ++i)
			merge_string(paper[i].begin(), paper[paper.size()-1-i].begin(), paper[i].size());
		paper.resize(paper.size() / 2);
	}
}

int main()
{
	std::list<std::pair<int, int>> 	dots;
	std::vector<std::string>		paper;
	std::string						line;
	std::string						folds;
	std::istringstream				ss;
	int								total = 0;
	int								width = 0;
	int								height = 0;

	while (std::getline(std::cin, line)) {
		if (!line.size())
			break;
		ss.str(line);
		std::pair<int, int> dot;
		ss >> dot.first; ss.ignore();
		ss >> dot.second;
		dots.push_back(dot);
		ss.clear();
	}
	while (std::getline(std::cin, line))
		folds.push_back(line[11]);
	for (auto &dot : dots) {
		width = std::max(width, dot.first);
		height = std::max(height, dot.second);
	}
	height += 1 + (height % 2);
	width += 1 + (width % 2);
	paper.resize(height, std::string(width, ' '));
	for (auto &dot : dots)
		paper[dot.second][dot.first] = '#';
	fold_paper(paper, folds[0]);
	for (auto &line : paper)
		total += count(line.begin(),line.end(), '#');
	std::cout << "Total: " << total << std::endl;
	return (0);
}