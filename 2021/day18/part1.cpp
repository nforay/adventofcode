#include <iostream>

typedef struct node {
	int			value = -1;
	struct node	*parent;
	struct node	*lchild;
	struct node	*rchild;
} t_node;

t_node	*create_node(t_node *parent, int value)
{
	t_node *node = new t_node;
	node->value = value;
	node->parent = parent;
	node->lchild = NULL;
	node->rchild = NULL;
	return (node);
}

void	free_tree(t_node *node)
{
	if (node->lchild)
		free_tree(node->lchild);
	if (node->rchild)
		free_tree(node->rchild);
	delete node;
}

/** 
 * @brief	Recursively convert a JSON-like string to a tree of nodes
 * @param	node	Root node of the tree/subtree
 * @param	str		JSON-like string to convert
 * @param	depth	Current depth of the tree/subtree
**/
void	extractsnailfish(t_node *node, const std::string &str, int depth)
{
	int count = 0;
	for (auto it = str.begin(); it != str.end(); it++) {
		if (*it == '[')
			count++;
		else if (*it == ']')
			count--;
		else if (*it == ',' && count == 1) {
			std::string	leftstr(++str.begin(), it);
			std::string	rightstr(++it, --str.end());
			node->lchild = create_node(node, -1);
			if (leftstr.size() > 4)
				extractsnailfish(node->lchild, leftstr, depth + 1);
			else if (leftstr.size() == 1)
				node->lchild->value = leftstr[0] - '0';
			node->rchild = create_node(node, -1);
			if (rightstr.size() > 4)
				extractsnailfish(node->rchild, rightstr, depth + 1);
			else if (rightstr.size() == 1)
				node->rchild->value = rightstr[0] - '0';
			break;
		}
	}
}

t_node	*leftmost(t_node *root)
{
	while (root->lchild)
		root = root->lchild;
	return (root);
}

t_node	*rightmost(t_node *root)
{
	while (root->rchild)
		root = root->rchild;
	return (root);
}

void	removechilds(t_node *node, int newvalue)
{
	if (node->lchild)
		delete node->lchild;
	if (node->rchild)
		delete node->rchild;
	node->lchild = NULL;
	node->rchild = NULL;
	node->value = newvalue;
}

void	addleft(t_node *node, int value)
{
	//node = node->parent;
	while (node->parent && node->parent->lchild == node)
		node = node->parent;
	if (node->parent)
		node = node->parent->lchild;
	while (node->rchild)
		node = node->rchild;
	node->value += value;
}

void	addright(t_node *node, int value)
{
	//node = node->parent;
	while (node->parent && node->parent->rchild == node)
		node = node->parent;
	if (node->parent)
		node = node->parent->rchild;
	while (node->lchild)
		node = node->lchild;
	node->value += value;
}

void	printjson(t_node *node, bool once, std::string &cmp);
void	explode(t_node *root, t_node *node)
{
	if (leftmost(root) != node->lchild)
		addleft(node->lchild, node->lchild->value);
	if (rightmost(root) != node->rchild)
	addright(node->rchild, node->rchild->value);
	removechilds(node, 0);
	while (node->parent)
		node = node->parent;
	std::string compare;
	printjson(node, true, compare);
	std::cerr << compare << std::endl;
}

void	splits(t_node *node)
{
	node->lchild = create_node(node, node->value / 2);
	node->rchild = create_node(node, node->value - node->lchild->value);
	node->value = -1;
	while (node->parent)
		node = node->parent;
	std::string compare;
	printjson(node, true, compare);
}

void reduce(t_node *root);
void	reducepairs(t_node *root, t_node *node, int depth)
{
	if (node->lchild)
		reducepairs(root, node->lchild, depth + 1);
	if (node->rchild)
		reducepairs(root, node->rchild, depth + 1);
	if (!node->lchild && !node->rchild) {
		if (depth > 4) {
			explode(root, node->parent);
			reduce(root);
		}
	}
}

void	reducevalue(t_node *root, t_node *node)
{
	if (node->lchild)
		reducevalue(root, node->lchild);
	if (node->rchild)
		reducevalue(root, node->rchild);
	if (node->value > 9) {
		splits(node);
		reduce(root);
	}
}

void	reduce(t_node *root)
{
	reducepairs(root, root, 0);
	reducevalue(root, root);
}

t_node	*add(t_node *lhs, t_node *rhs)
{
	t_node *newroot = create_node(NULL, -1);
	lhs->parent = newroot;
	rhs->parent = newroot;
	newroot->lchild = lhs;
	newroot->rchild = rhs;
	return (newroot);
}

void	printnodelevel(t_node *node, int depth, int targetdepth)
{
	if (node->lchild && depth < targetdepth)
		printnodelevel(node->lchild, depth + 1, targetdepth);
	if (node->rchild && depth < targetdepth)
		printnodelevel(node->rchild, depth + 1, targetdepth);
	if (depth == targetdepth && node->value != -1)
		std::cerr << node->value << "\t";
}

void	printjson(t_node *node, bool once, std::string &cmp)
{
	if (node->lchild)
		cmp.push_back('[');
	if (!node->lchild) {
		cmp += std::to_string(node->value);
		if (node && node == node->parent->lchild)
			cmp.push_back(',');
	} else
		printjson(node->lchild, false, cmp);
	if ((once && cmp.back() != ',') || ((node->lchild && node->rchild) && (node->lchild->lchild && node->rchild->rchild)))
		cmp.push_back(',');
	if (node->rchild) {
		printjson(node->rchild, false, cmp);
		cmp.push_back(']');
		if (node->parent && node->parent->rchild->value >= 0 && node->parent->parent)
			cmp.push_back(',');
	}
}

int magnitude(t_node *node)
{
	std::cerr << "magnitude" << std::endl;
	if (node->lchild)
		magnitude(node->lchild);
	if (node->rchild)
		magnitude(node->rchild);
	if (node->parent)
		node = node->parent;
	removechilds(node, 3 * node->lchild->value + 2 * node->rchild->value);
	return (node->value);
}

int		main()
{
	std::string		str;
	t_node*			root = NULL;
	t_node*			node = NULL;
	int fail = 0;

	while (std::getline(std::cin, str)) {
		std::string compare;
		if (!root) {
			root = create_node(NULL, -1);
			extractsnailfish(root, str, 1);
			printjson(root, true, compare);
		} else {
			node = create_node(NULL, -1);
			extractsnailfish(node, str, 1);
			printjson(node, true, compare);
		}
		std::cerr << str << std::endl;
		std::cerr << compare << " " << (str == compare ? "\e[32m[OK]\e[39m" : "\e[31m[KO]\e[39m") << std::endl;
		if (str != compare) {
			fail++;
			free_tree(root);
			continue;
		}
		if (node != NULL) {
			compare.clear();
			printjson(root, true, compare);
			std::cerr << compare << " + ";
			compare.clear();
			printjson(node, true, compare);
			std::cerr << compare << " = " << std::endl;
			root = add(root, node);
			reduce(root);
		}
		compare.clear();
		printjson(root, true, compare);
		std::cerr << "\t\t\t" << compare << std::endl;
		//std::cout << "Answer: " << "" << std::endl;
		if (node) {
			node = NULL;
		}
	}
	std::cout << "Answer: " << magnitude(root) << std::endl;
	free_tree(root);
	return (0);
}