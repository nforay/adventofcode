#include <iostream>
#include <string>
#include <fstream>
#include <map>

class point {
    public:
    int _x = 0;
    int _y = 0;
    point   &operator+=(const point& rhs) {
        this->_x += rhs._x;
        this->_y += rhs._y;
        return *this;
    }
    point   &operator=(const point& rhs) {
        this->_x = rhs._x;
        this->_y = rhs._y;
        return *this;
    }
};

int main() {
    std::ifstream                       input("input.txt");
    std::string                         line;
    point                               head, tail;
    std::map<std::pair<int, int>, bool> visited;

    while (getline(input, line)) {
        int move = atoi(line.c_str() + 2);
        while (move--) {
            point oldhead = head;
            switch (line[0])
            {
            case 'U':
                head += point{0, 1};
                break;
            case 'D':
                head += point{0, -1};
                break;
            case 'L':
                head += point{-1, 0};
                break;
            default:
                head += point{1, 0};
                break;
            }
            if (abs(head._x - tail._x) > 1 || abs(head._y - tail._y) > 1)
                tail = oldhead;
            visited[std::pair<int, int>(tail._x, tail._y)] = true;
        }
    }
    std::cout << visited.size();
    return 0;
}
