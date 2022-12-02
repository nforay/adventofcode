#include <iostream>

enum Item {
	rock = 0,
	paper = 1,
	scissors = 2
};

int getWinner(Item &opponent, Item &player)
{
	if ((player + 1) % 3 == opponent)
        return -1;
    else if (player == opponent)
        return 0;
    else
        return 1;
}

int main() {
	char	buffer[4];
	int		score, total = 0;
	Item	lhs, rhs;

	while (std::cin.getline(buffer,4)) {
		lhs = (Item)(buffer[0] - 'A');
		rhs = (Item)(buffer[2] - 'X');
		switch (getWinner(lhs, rhs)) {
			case -1: //loose
				score = 1 + (int)rhs;
				break;
			case 0: //tie
				score = 4 + (int)rhs;
				break;
			case 1: //win
				score = 7 + (int)rhs;
				break;
		}
		total += score;
	}
	std::cout << total << std::endl;
	return 0;
}