#include <iostream>
#include <vector>
#include <stack>

class octopus
{
	public:
		octopus(std::stack<octopus*> *flashed_stack, int value) : m_last_flash(0), m_value(value), m_flashed_stack(flashed_stack) {};
		~octopus() {};

		void increment() {
			m_value++;
		};
		void update(const int &turn) {
			if (m_value > 9 && turn > m_last_flash)
				this->flash(turn);
		}
		void flash(const int &turn) {
			m_flashed_stack->push(this);
			m_last_flash = turn;
			for (auto neighbors : m_neighbors) {
				(*neighbors)->increment();
				(*neighbors)->update(turn);
			}
		};
		int						m_last_flash;
		std::vector<octopus**>	m_neighbors;
		int						m_value;
		std::stack<octopus*>	*m_flashed_stack;
};

int main()
{
	std::string							line;
	octopus*							octopus_grid[10][10];
	int									flash_count = 0;
	std::stack<octopus*>				flashed_stack;
	std::vector<std::pair<int, int>>	neighbors({{1, 1}, {1, 0}, {1, -1}, {0, 1}, {0, -1}, {-1, 1}, {-1, 0}, {-1, -1}});

	for (int y = 0; y < 10; ++y) {
		std::getline(std::cin, line);
		for (int x = 0; x < 10; ++x) {
			octopus_grid[y][x] = new octopus(&flashed_stack, line[x] - '0');
			for (auto neighbor : neighbors)
				if (y+neighbor.first >= 0 && y+neighbor.first < 10 && x+neighbor.second >= 0 && x+neighbor.second < 10)
					octopus_grid[y][x]->m_neighbors.push_back(&octopus_grid[y+neighbor.first][x+neighbor.second]);
		}
	}
	std::cerr << "Before any steps:\n";
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j)
					std::cerr << octopus_grid[i][j]->m_value;
				std::cerr << "\n";
			}
	for (int step = 1; step <= 100; ++step) {
		for (int y = 0; y < 10; ++y)
			for (int x = 0; x < 10; ++x)
				octopus_grid[y][x]->increment();
		for (int y = 0; y < 10; ++y)
			for (int x = 0; x < 10; ++x)
				octopus_grid[y][x]->update(step);
		while (flashed_stack.size()) {
			flashed_stack.top()->m_value = 0;
			flash_count++;
			flashed_stack.pop();
		}
		if (step < 10 || step % 10 == 0) {
			std::cerr << "After step " << step << ":\n";
			for (int i = 0; i < 10; ++i) {
				for (int j = 0; j < 10; ++j)
					std::cerr << (!octopus_grid[i][j]->m_value ? "\e[31m" : "\e[39m") << octopus_grid[i][j]->m_value;
				std::cerr << "\e[39m\n";
			}
		}
	}
	std::cout << "Answer: " << flash_count << std::endl;
	return (0);
}