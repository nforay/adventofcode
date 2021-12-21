#include <iostream>
#include <vector>

/**
 * I'd say this day's puzzle was the hardest so far, the goal is to deserialize
 * what looks like a json string to a binary tree, but the BT don't work as you would
 * expect, the values are stored on the leafs and not on the nodes. You then Add
 * two Binary Trees together and reduce them using some operations. The operations are
 * nothing close to what you would expect (balancing a tree and such), but the code
 * is still readable. Reminded me a lot when I made the std::map container from scratch.
 */

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

t_node	*copy_tree(t_node *node, t_node *parent)
{
	t_node *newnode = create_node(parent, node->value);
	if (node->lchild)
		newnode->lchild = copy_tree(node->lchild, newnode);
	if (node->rchild)
		newnode->rchild = copy_tree(node->rchild, newnode);
	return (newnode);
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
	while (node->parent && node->parent->rchild == node)
		node = node->parent;
	if (node->parent)
		node = node->parent->rchild;
	while (node->lchild)
		node = node->lchild;
	node->value += value;
}

void	explode(t_node *root, t_node *node)
{
	if (leftmost(root) != node->lchild)
		addleft(node->lchild, node->lchild->value);
	if (rightmost(root) != node->rchild)
	addright(node->rchild, node->rchild->value);
	removechilds(node, 0);
	while (node->parent)
		node = node->parent;
}

void	splits(t_node *node)
{
	node->lchild = create_node(node, node->value / 2);
	node->rchild = create_node(node, node->value - node->lchild->value);
	node->value = -1;
	while (node->parent)
		node = node->parent;
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

int magnitude(t_node *node)
{
	if (node->lchild->lchild)
		magnitude(node->lchild);
	if (node->rchild->lchild)
		magnitude(node->rchild);
	node->value = 3 * node->lchild->value + 2 * node->rchild->value;
	return (node->value);
}

int		main()
{
	std::string					str;
	t_node*						root = NULL;
	t_node*						node = NULL;
	std::vector<std::string>	snailfishs;
	int							magnitudemax = 0;

	while (std::getline(std::cin, str))
		snailfishs.push_back(str);
	for (auto ita = snailfishs.begin(); ita != snailfishs.end(); ita++) {
		root = create_node(NULL, -1);
		extractsnailfish(root, *ita, 1);
		for (auto itb = snailfishs.begin(); itb != snailfishs.end(); itb++) {
			if (*ita == *itb)
				continue;
			node = create_node(NULL, -1);
			extractsnailfish(node, *itb, 1);
			t_node *altroot = copy_tree(root, NULL);
			t_node *altnode = copy_tree(node, NULL);
			t_node *scoperoot = copy_tree(root, NULL);
			altnode = add(altnode, altroot);
			scoperoot = add(scoperoot, node);
			reduce(scoperoot);
			reduce(altnode);
			magnitudemax = std::max(magnitudemax, std::max(magnitude(scoperoot), magnitude(altnode)));
			free_tree(scoperoot);
			free_tree(altnode);
		}
		free_tree(root);
	}
	std::cout << "Answer: " << magnitudemax << std::endl;
	return (0);
}