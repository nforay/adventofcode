#include <iostream>
#include <vector>
#include <stack>

void	line_score(const std::string &str, std::vector<long> &scores)
{
	long				score = 0;
	std::stack<char>	symbols;

	for (auto &c : str) {
		switch (c) {
			case ')':
				if (symbols.top() != '(')
					return;
				symbols.pop();
				break;
			case ']':
				if (symbols.top() != '[')
					return;
				symbols.pop();
				break;
			case '}':
				if (symbols.top() != '{')
					return;
				symbols.pop();
				break;
			case '>':
				if (symbols.top() != '<')
					return;
				symbols.pop();
				break;
			default:
				symbols.push(c);
		}
	}
	while (symbols.size()) {
		switch (symbols.top()) {
			case '(':
				score = score * 5 + 1;
				symbols.pop();
				break;
			case '[':
				score = score * 5 + 2;
				symbols.pop();
				break;
			case '{':
				score = score * 5 + 3;
				symbols.pop();
				break;
			case '<':
				score = score * 5 + 4;
				symbols.pop();
				break;
			default:
				std::cerr << "Unexpected symbol: " << symbols.top() << std::endl;
				return;
		}
	}
	scores.push_back(score);
	return;
}

int main()
{
	std::string				line;
	std::vector<long>		scores;

	while (std::getline(std::cin, line))
		line_score(line, scores);
	sort(scores.begin(), scores.end());
	std::cout << "Answer: " << scores[scores.size() / 2] << std::endl;
	return (0);
}