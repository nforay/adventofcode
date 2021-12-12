#include <iostream>
#include <unordered_map>
#include <vector>

class node
{
	public:
		node(const std::string &str) : name(str) {};
		~node() {};

		std::string			name;
		std::vector<node*>	neighbors;
};

int DFS(node *position, std::unordered_map<node*, int> visited, bool smalltwice)
{
	if (position->name == "end")
		return (1);
	int	total = 0;
	if (islower(position->name[0])) {
		visited[position]++;
		smalltwice = (visited[position] == 2 ? true : smalltwice);
	}
	for (auto neighbor : position->neighbors)
		if (isupper(neighbor->name[0]) || visited[neighbor] < (smalltwice ? 1 : 2))
			total += DFS(neighbor, visited, smalltwice);
	return (total);
}

int main()
{
	std::string								line;
	std::unordered_map<std::string, node*>	node_map;
	int										total = 0;

	while (std::getline(std::cin, line)) {
		std::string str1 = line.substr(0, line.find('-'));
		std::string str2 = line.substr(line.find('-') + 1);
		if (!node_map.contains(str1))
			node_map.insert(std::pair<std::string, node*>(str1, new node(str1)));
		if (!node_map.contains(str2))
			node_map.insert(std::pair<std::string, node*>(str2, new node(str2)));
		node_map[str1]->neighbors.push_back(node_map[str2]);
		node_map[str2]->neighbors.push_back(node_map[str1]);
	}
	std::unordered_map<node*, int> visited({{node_map["start"], 2}});
	total = DFS(node_map["start"], visited, false);
	std::cout << "Total: " << total << std::endl;
	for (auto node : node_map)
		delete node.second;
	return (0);
}