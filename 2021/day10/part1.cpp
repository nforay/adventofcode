#include <iostream>
#include <map>
#include <stack>

int	line_score(std::string &str, std::map<char, int> &scale)
{
	std::stack<char>	symbols;
	for (auto &c : str) {
		switch (c) {
			case ')':
				if (symbols.top() != '(')
					return (scale[c]);
				symbols.pop();
				break;
			case ']':
				if (symbols.top() != '[')
					return (scale[c]);
				symbols.pop();
				break;
			case '}':
				if (symbols.top() != '{')
					return (scale[c]);
				symbols.pop();
				break;
			case '>':
				if (symbols.top() != '<')
					return (scale[c]);
				symbols.pop();
				break;
			default:
				symbols.push(c);
		}
	}
	return (0);
}

int main()
{
	std::string				line;
	std::map<char, int>		scale = {{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
	int						total = 0;

	while (std::getline(std::cin, line))
		total += line_score(line, scale);
	std::cout << "Answer: " << total << std::endl;
	return (0);
}