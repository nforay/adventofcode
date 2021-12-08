#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>

int	count_occurences(std::string const &str1, std::string const &str2)
{
	int	count = 0;
	for (auto &c : str1) {
		for (auto &d : str2) {
			if (c == d)
				count++;
		}
	}
	return count;
}

int main()
{
	std::string													line;
	int															total = 0;

	while (std::getline(std::cin, line)) {
		std::vector<std::string>								digits;
		std::vector<std::string>								values;
		std::unordered_map<std::string, std::pair<int, int>>	translated;
		std::istringstream										iss(line);
		int														nbr = 0;

		while (iss >> line) {
			if (line.size() == 1) {
				continue;
			} else if (digits.size() < 10) {
				digits.push_back(line);
			} else {
				values.push_back(line);
			}
		}
		sort(digits.begin(), digits.end(), [](std::string a, std::string b) { return a.size() < b.size(); });
		translated.insert({ digits[0], {1, 0} }); // 1 is known
		translated.insert({ digits[1], {7, 1} }); // 7 is known
		translated.insert({ digits[2], {4, 2} }); // 4 is known
		translated.insert({ digits[9], {8, 9} }); // 8 is known
		int digit2 = 0;
		for (int i = 3; i < digits.size(); i++) {
			if (translated.contains(digits[i]))
				continue;
			if (count_occurences(digits[2], digits[i]) == 4 && digits[i].size() == 6) { // guess 9 knowing 4
				translated.insert({ digits[i], {9, i} });
			} else if (count_occurences(digits[2], digits[i]) == 3 && count_occurences(digits[0], digits[i]) == 2 && digits[i].size() == 6) { // guess 0 knowing 4 and 1
				translated.insert({ digits[i], {0, i} });
			} else if (count_occurences(digits[0], digits[i]) == 2 && digits[i].size() == 5) { // guess 3 knowing 1
				translated.insert({ digits[i], {3, i} });
			} else if (count_occurences(digits[2], digits[i]) == 2 && digits[i].size() == 5) { // guess 2 knowing 4
				translated.insert({ digits[i], {2, i} });
				digit2 = i;
			}
		}
		for (int j = 3; j < digits.size(); j++) {
			if (translated.contains(digits[j]))
				continue;
			if (count_occurences(digits[j], digits[digit2]) == 4 && digits[j].size() == 6) {
				translated.insert({ digits[j], {6, j} }); // guess 6 knowing 2
			} else if (count_occurences(digits[j], digits[digit2]) == 3 && digits[j].size() == 5) {
				translated.insert({ digits[j], {5, j} }); // guess 5 knowing 2
			}
		}		
		int  i = 0;
		for (auto it = values.rbegin(); it != values.rend(); it++, i++) {
			for (auto & digit : translated) {
				if ((*it).size() != digit.first.size() || count_occurences(*it, digit.first) != (*it).size())
					continue;
				nbr += (digit.second.first * pow(10, i));
				break;
			}
		}
		total += nbr;
	}
	std::cout << "Answer: " << total << std::endl;
	return (0);
}