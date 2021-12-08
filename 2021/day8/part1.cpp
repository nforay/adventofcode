#include <iostream>
#include <sstream>

int main()
{
	std::string		line;
	int				count = 0;

	while (std::getline(std::cin, line)) {
		line.erase(line.begin(), line.begin() + line.find('|') + 2);
		std::istringstream	iss(line);
		while (iss >> line) {
			for (int i : {2, 3, 4, 7})
				if (line.size() == i)
					count++;
		}
	}
	std::cout << "Answer: " << count << std::endl;
	return (0);
}