#include <iostream>

int main()
{
	int value = 0;
	int lastvalue = 0;
	int answer = 0;
	while (std::cin >> value)
	{
		if (lastvalue && value > lastvalue)
			answer++;
		lastvalue = value;
	}
	std::cout << "Answer: " << answer << std::endl;
	return (0);
}