#include <iostream>
#include <stack>

int	line_score(const std::string &str)
{
	std::stack<char>	symbols;
	for (auto &c : str) {
		switch (c) {
			case ')': if (symbols.top() != '(') return (3); symbols.pop(); break;
			case ']': if (symbols.top() != '[') return (57); symbols.pop(); break;
			case '}': if (symbols.top() != '{') return (1197); symbols.pop(); break;
			case '>': if (symbols.top() != '<') return (25137); symbols.pop(); break;
			default: symbols.push(c);
		}
	}
	return (0);
}

int main()
{
	std::string				line;
	int						total = 0;

	while (std::getline(std::cin, line))
		total += line_score(line);
	std::cout << "Answer: " << total << std::endl;
	return (0);
}