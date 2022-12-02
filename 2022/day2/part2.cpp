#include <iostream>

int getMove(int opponent, int outcome)
{
	switch (outcome) {
		case 0:
			return 1 + ((opponent - 1 < 0 ? 2 : opponent - 1) % 3);
		case 1:
			return 4 + opponent;
		default:
			return 7 + ((opponent + 1) % 3);
	}
}

int main() {
	char	buffer[4];
	int		total = 0;

	while (std::cin.getline(buffer,4))
		total += getMove(buffer[0] - 'A', buffer[2] - 'X');
	std::cout << total << std::endl;
	return 0;
}