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

int DFS(node *position, std::unordered_map<node*, bool> visited, std::vector<node*> path)
{
	if (position->name == "end") {
		path.push_back(position);
		for (auto nod : path) {
			std::cerr << nod->name << ",";
		}
		std::cerr << "\b \n";
		return (1);
	}
	if (islower(position->name[0]))
		visited[position] = true;
	path.push_back(position);
	int	total = 0;
	for (auto neighbor : position->neighbors)
		if (isupper(neighbor->name[0]) || !visited.contains(neighbor))
			total += DFS(neighbor, visited, path);
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
	std::unordered_map<node*, bool> visited({{node_map["start"], true}});
	total = DFS(node_map["start"], visited, {});
	std::cout << "Total: " << total << std::endl;
	for (auto node : node_map)
		delete node.second;
	return (0);
}