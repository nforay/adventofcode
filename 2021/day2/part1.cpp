#include <iostream>

int main()
{
	std::string	command;
	int			value;
	int			depth = 0;
	int			hpos = 0;
	while (std::cin >> command >> value)
	{
		switch(command[0])
		{
			case 'f':
				hpos += value;
				break;
			case 'd':
				depth += value;
				break;
			case 'u':
				depth -= value;
				break;
		}
	}
	std::cout << "Answer: " << depth * hpos << std::endl;
	return (0);
}