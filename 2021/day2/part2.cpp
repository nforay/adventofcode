#include <iostream>

int main()
{
	std::string	command;
	int			value;
	int			depth = 0;
	int			hpos = 0;
	int			aim = 0;
	while (std::cin >> command >> value)
	{
		switch(command[0])
		{
			case 'f':
				hpos += value;
				depth += aim * value;
				break;
			case 'd':
				aim += value;
				break;
			case 'u':
				aim -= value;
				break;
		}
	}
	std::cout << "Answer: " << depth * hpos << std::endl;
	return (0);
}