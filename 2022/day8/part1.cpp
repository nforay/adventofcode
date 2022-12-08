#include <iostream>
#include <string>
#include <fstream>

#define WIDTH 99

struct Tree {
    Tree    *neighbours[4] = {NULL, NULL, NULL, NULL};
    char    size;
    bool    seen = false;
};

enum Direction {
    Up,
    Down,
    Left,
    Right
};

void countTrees(Tree *position, Direction dir, char max = 0) {
    if (position->size > max)
        position->seen = true;
    if (max == '9')
        return;
    if (position->neighbours[dir])
        countTrees(position->neighbours[dir], dir, std::max(position->size, max));
}

int main() {
    std::ifstream       input("input.txt");
    std::string         line{WIDTH, '\0'};
    Tree                forest[WIDTH * WIDTH];
    int                 total = 0;

    while (getline(input, line)) {
        for (const char &c : line) {
            if (total % WIDTH) forest[total].neighbours[Direction::Left] = &forest[total - 1]; else forest[total].seen = true;
            if (total % WIDTH != WIDTH - 1) forest[total].neighbours[Direction::Right] = &forest[total + 1]; else forest[total].seen = true;
            if (total >= WIDTH) forest[total].neighbours[Direction::Up] = &forest[total - WIDTH]; else forest[total].seen = true;
            if (total < (WIDTH * (WIDTH - 1))) forest[total].neighbours[Direction::Down] = &forest[total + WIDTH]; else forest[total].seen = true;
            forest[total++].size = c;
        }
    }
    for (int i = 1; i < WIDTH - 1; i++) {
        countTrees(&forest[i], Direction::Down);
        countTrees(&forest[WIDTH * WIDTH - i - 1], Direction::Up);
        countTrees(&forest[i * WIDTH], Direction::Right);
        countTrees(&forest[WIDTH + i * WIDTH - 1], Direction::Left);
    }
    total = 0;
    for (int i = 0; i < WIDTH * WIDTH; i++)
        total += forest[i].seen ? 1 : 0;
    std::cout << total;
    return 0;
}
