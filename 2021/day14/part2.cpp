#include <iostream>
#include <map>
#include <algorithm>

int main()
{
	std::string									str;
	std::string									line;
	std::map<std::pair<char, char>, char>		rules;
	std::map<std::pair<char, char>, long>		pairs;
	std::map<char, long>						charcount;
	long										least = __LONG_MAX__;
	long										most = 0;

	while (std::getline(std::cin, line)) {
		if (str.empty())
			str.swap(line);
		if (!line.empty())
			rules.emplace(std::make_pair(line[0], line[1]), line[6]);
	}
	for (std::string::iterator itb = str.begin(), ite = ++str.begin(); ite != str.end(); itb++, ite++)
		pairs[{*itb, *ite}]++;
	for (int step = 0; step < 40; ++step) {
		std::map<std::pair<char, char>, long>	next_pairs;
		for (auto &pair : pairs) {
			next_pairs[{pair.first.first, rules[pair.first]}] += pairs[pair.first];
			next_pairs[{rules[pair.first], pair.first.second}] += pairs[pair.first];
		}
		pairs = next_pairs;
	}
	for (auto &pair : pairs)
		charcount[pair.first.first] += pair.second;
	charcount[str.back()]++;
	for (auto &count : charcount) {
		least = std::min(least, count.second);
		most = std::max(most, count.second);
	}
	std::cout << "Answer: " << most - least << std::endl;
	return (0);
}