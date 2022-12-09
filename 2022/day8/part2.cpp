#include <iostream>
#include <string>
#include <fstream>

#define WIDTH 99

struct Tree {
    Tree    *neighbours[4] = {NULL, NULL, NULL, NULL};
    char    size;
};

enum Direction {
    Up,
    Down,
    Left,
    Right
};

int countTrees(Tree *position, Direction dir, char me, char max = 0) {
    if (!position)
        return 0;
    if (position->size >= me)
        return 1;
    return 1 + countTrees(position->neighbours[dir], dir, me, std::max(position->size, max));
}

int main() {
    std::ifstream       input("input.txt");
    std::string         line(WIDTH, '\0');
    Tree                forest[WIDTH * WIDTH];
    int                 total = 0;

    while (getline(input, line)) {
        for (const char &c : line) {
            if (total % WIDTH) forest[total].neighbours[Direction::Left] = &forest[total - 1];
            if (total % WIDTH != WIDTH - 1) forest[total].neighbours[Direction::Right] = &forest[total + 1];
            if (total >= WIDTH) forest[total].neighbours[Direction::Up] = &forest[total - WIDTH];
            if (total < (WIDTH * (WIDTH - 1))) forest[total].neighbours[Direction::Down] = &forest[total + WIDTH];
            forest[total++].size = c;
        }
    }
    total = 0;
    for (int i = WIDTH + 1; i < WIDTH * (WIDTH - 1) - 1; i++) {
        int score = 1;
        if (!forest[i].neighbours[0] || !forest[i].neighbours[1] || !forest[i].neighbours[2] || !forest[i].neighbours[3])
            continue;
        for (Direction dir : {Direction::Up, Direction::Down, Direction::Left, Direction::Right})
            score *= countTrees(forest[i].neighbours[dir], dir, forest[i].size);
        total = std::max(score, total);
    }
    std::cout << total << std::endl;
    return 0;
}
