#include <iostream>
#include <vector>
#include <list>
#include <sstream>

// set to 1 when using https://github.com/nothings/stb
#define STB 0

#ifdef STB
	#define STB_IMAGE_IMPLEMENTATION
	#include "stb_image.h"

	#define STB_IMAGE_WRITE_IMPLEMENTATION
	#include "stb_image_write.h"
#endif

#ifdef STB_IMAGE_WRITE_IMPLEMENTATION
	void vec_to_png(const std::vector<std::string> &paper)
	{
		static int filenum = 0;
		std::vector<uint8_t> pixels(paper[0].size() * paper.size() * 3);
		int index = 0;
		for (int j = 0; j < paper.size(); ++j) {
			for (int i = 0; i < paper[0].size(); ++i) {
				int r, g, b;
				r = g = b = (paper[j][i] == '#' ? 255 : 0);
				pixels[index++] = r;
				pixels[index++] = g;
				pixels[index++] = b;
			}
		}
		std::string filename = "out_" + std::to_string(filenum++) + ".png";
		stbi_write_png(filename.c_str(), paper[0].size(), paper.size(), 3, (void*)pixels.data(), paper[0].size() * 3);
	}
#endif

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
	std::list<std::pair<int, int>>	dots;
	std::vector<std::string>		paper;
	std::string						folds;
	std::string						line;
	std::istringstream				ss;
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
#ifdef STB_IMAGE_WRITE_IMPLEMENTATION
	vec_to_png(paper);
#endif
	for (auto &fold : folds) {
		fold_paper(paper, fold);
#ifdef STB_IMAGE_WRITE_IMPLEMENTATION
		vec_to_png(paper);
#endif
	}
	for (auto &line : paper)
		std::cout << line << std::endl;
	return (0);
}