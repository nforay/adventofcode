#include <iostream>
#include <map>

int main()
{
	std::string								str;
	std::map<std::string, char>				rules;
	std::string								line;
	std::map<char, int>						charusage;

	while (std::getline(std::cin, line)) {
		if (str.empty())
			str.swap(line);
		if (!line.empty()) {
			char	value = line[6];
			line.resize(2);
			rules.emplace(line, value);
		}
	}
	std::cerr << "Template:\t" << str << std::endl;
	for (int step = 1; step < 11; ++step) {
		for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
			line.replace(line.begin(), line.end(), it, it+2);
			if (rules.contains(line))
				it = str.insert(++it, rules.at(line));
		}
		std::cerr << "After step " << step << ":\t" << str << "\n";
	}
	for (auto &c : str)
		charusage[c]++;
	auto most = std::max_element(charusage.begin(), charusage.end(), [](const std::pair<char, int>& p1, const std::pair<char, int>& p2) { return p1.second < p2.second; })->second;
	auto least = std::max_element(charusage.begin(), charusage.end(), [](const std::pair<char, int>& p1, const std::pair<char, int>& p2) { return p1.second > p2.second; })->second;
	std::cout << "Answer: " << most - least << std::endl;
	return (0);
}