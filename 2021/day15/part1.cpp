#include <iostream>
#include <limits>
#include <vector>
#include <queue>

typedef struct coords {
	int x;
	int y;
} coords;
const coords dirs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

auto comp = [](const std::pair<int, int> &a, const std::pair<int, int> &b) { return a.second > b.second; };

int main()
{
	std::string								line;
	std::vector<std::string>				lines;

	while (std::getline(std::cin, line))
		lines.push_back(line);
	std::vector<std::vector<std::pair<int, int>>>	Graph(lines.size() * lines[0].size());
	for (int y = 0; y < lines.size(); y++)
		for (int x = 0; x < lines[0].size(); x++)
			for (const auto &dir : dirs) {
				if (y + dir.y >= 0 && y + dir.y < lines.size() &&
				x + dir.x >= 0 && x + dir.x < lines[0].size()) // building a graph[node index] = {neighbour index, cost}
					Graph[y*lines[0].size()+x].push_back(std::make_pair((y + dir.y) * lines[0].size() + x + dir.x, lines[y + dir.y][x + dir.x] - '0'));
			}
	std::vector<int> Distances(Graph.size(), std::numeric_limits<int>::max());
	Distances[0] = 0; // risk 0 for start position
	std::vector<int> Parents(Graph.size(), -1);
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)> Q(comp);
	Q.push(std::make_pair(0, 0)); // Adding start node
	while (!Q.empty()) { // find cheapest path using Dijkstra
		int v = Q.top().first;
		int w = Q.top().second;
		Q.pop();
		if (w <= Distances[v]) {
			for (const auto& i : Graph[v]) {
				auto v2 = i.first;
				auto w2 = i.second;
				if (Distances[v] + w2 < Distances[v2]) {
					Distances[v2] = Distances[v] + w2; 
					Parents[v2] = v; 
					Q.push(std::make_pair(v2, Distances[v2]));
				}
			}
		}
	}
	std::cout << "Answer: " << Distances.back() << std::endl;
	return (0);
}