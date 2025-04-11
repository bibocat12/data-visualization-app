
#include "../../../header/State/AVL/AVLTree.h"

AVLTree::AVLTree()
{
	root = nullptr;
}

AVLTree::~AVLTree()
{
	clear();
}

void AVLTree::insert(int value)
{
	root = insert(root, value);
	int order = 0;
	reorder(root, order);


}
void AVLTree::remove(int value)
{
	root = remove(root, value);
}
void AVLTree::search(int value)
{
	search(root, value);
}
std::vector<int> AVLTree::searchPath(int value)
{
	Node* node = root;
	std::vector<int> path;
	while (node != nullptr)
	{
		path.push_back(node->order);
		if (value < node->value)
			node = node->left;
		else if (value > node->value)
			node = node->right;
		else
		{
			break;
		}
	}
	return path;
}
void AVLTree::create(std::vector<int> elements)
{
	root = create(root, elements);
	int order = 0;
	reorder(root, order);
}
std::vector<int> AVLTree::getAllElements()
{
	std::vector<int> elements;
	inorder(root, elements);
	return elements;
}
std::vector<int> AVLTree::getInorderDepth()
{
	std::vector<int> elements;
	inorderDepth(root, 0, elements);
	return elements;
}
std::vector<int> AVLTree::getParent()
{
	std::vector<int> elements;
	inorderParent(root, nullptr, elements);
	return elements;
}
void AVLTree::clear()
{
	clear(root);
	root = nullptr;
}

bool AVLTree::isParent(int value, int child)
{
	Node* node = search(root, value);
	if (node == nullptr)
		return false;
	if (node->left != nullptr && node->left->value == child)
		return true;
	if (node->right != nullptr && node->right->value == child)
		return true;
	return false;
}

int AVLTree::countChild(int value)
{
	Node* node = search(root, value);
	if (node == nullptr)
		return -1;
	int count = 0;
	if (node->left != nullptr)
		count++;
	if (node->right != nullptr)
		count++;
	return count;
}

int AVLTree::findMinRight(int value)
{
	Node* node = search(root, value);
	if (node == nullptr)
		return -1;
	if (node->right == nullptr)
		return -1;
	Node* min = minValueNode(node->right);
	return min->value;

}

std::vector<AVLTree::TreeSnapshot> AVLTree::insertSnapshots(int value)
{
	std::vector<TreeSnapshot> snapshots;
	root = insertSnapshot(root, value, snapshots);
	recordSnapshot(snapshots, "end", root);
	return snapshots;

}

std::vector<AVLTree::TreeSnapshot> AVLTree::removeSnapshots(int value)
{
	std::vector<TreeSnapshot> snapshots;
	root = removeSnapshot(root, value, snapshots);
	recordSnapshot(snapshots, "end", root);
	return snapshots;

}

std::vector<int> AVLTree::recordInorder()
{
	std::vector<int> elements;
	recordInorder(root, elements);
	return elements;
}




AVLTree::Node* AVLTree::insert(Node* node, int value)
{
	if (node == nullptr)
		return new Node(value);

	if (value < node->value)
	{
		node->left = insert(node->left, value);

	}
	else if (value > node->value)
	{

		node->right = insert(node->right, value);
	}
	else
		return node;

	node->height = std::max(height(node->left), height(node->right)) + 1;

	return balance(node, value);
}
AVLTree::Node* AVLTree::insertSnapshot(Node*& node, int value, std::vector<TreeSnapshot>& snapshot)
{
	
	if (node == nullptr)
	{
		return new Node(value);
	}
	recordSnapshot(snapshot, "find", node);
	if (value < node->value)
		node->left = insertSnapshot(node->left, value, snapshot);

	else if (value > node->value)
	{
		node->right = insertSnapshot(node->right, value, snapshot);
	}
	else
	{
		return node;
	}
	node->height = std::max(height(node->left), height(node->right)) + 1;

	int balance = getBalance(node);
	recordSnapshot(snapshot, "check" + std::to_string(balance), node);
	if (balance > 1)
	{
		bool is;
		if (value > node->left->value)
		{
			node->left = rotateLeft(node->left);
			recordSnapshot(snapshot, "rotateLR", node);
			is = true;
		}


		node = rotateRight(node);
		recordSnapshot(snapshot, "rotateRR", node);
		return node;
	}
	if (balance < -1)
	{
		if (value < node->right->value)
		{

			node->right = rotateRight(node->right);
			recordSnapshot(snapshot, "rotateRL", node);
		}

		node = rotateLeft(node);
		recordSnapshot(snapshot, "rotateLL", node);
		return node;
	}

	return node;

}
AVLTree::Node* AVLTree::removeSnapshot(Node*& node, int value, std::vector<TreeSnapshot>& snapshot)
{
	if (node == nullptr)
		return node;
	recordSnapshot(snapshot, "find", node);
	// Traverse to the node to delete.
	if (value < node->value)
		node->left = removeSnapshot(node->left, value, snapshot);
	else if (value > node->value)
		node->right = removeSnapshot(node->right, value, snapshot);
	else {
		// Node to delete found.
		if (node->left == nullptr || node->right == nullptr) {
			Node* temp = node->left ? node->left : node->right;
			if (temp == nullptr) {  // No child
				temp = node;
				node = nullptr;
				recordSnapshot(snapshot, "removeNoChild", temp);
			}
			else {
				// One child: copy the child’s data.
				*node = *temp;
				recordSnapshot(snapshot, "removeOneChild", node);
			}
			delete temp;
		}
		else {
			// Two children: get the inorder successor.
			Node* temp = minValueNode(node->right);
			int valueTmp = temp->value;
			node->right = replaceSnapshots(node, node->right, snapshot);



		}
	}

	// If the tree had only one node.
	if (node == nullptr)
		return node;

	// Update height.
	node->height = std::max(height(node->left), height(node->right)) + 1;

	// Check balance and record snapshot.
	int balance = getBalance(node);
	recordSnapshot(snapshot, "check" + std::to_string(balance), node);

	// Left Left Case.
	if (balance > 1 && getBalance(node->left) >= 0) {
		node = rotateRight(node);
		recordSnapshot(snapshot, "rotateRR", node);
		return node;
	}
	// Left Right Case.
	if (balance > 1 && getBalance(node->left) < 0) {
		node->left = rotateLeft(node->left);
		recordSnapshot(snapshot, "rotateLR", node);
		node = rotateRight(node);
		recordSnapshot(snapshot, "rotateRR", node);
		return node;
	}
	// Right Right Case.
	if (balance < -1 && getBalance(node->right) <= 0) {
		node = rotateLeft(node);
		recordSnapshot(snapshot, "rotateLL", node);
		return node;
	}
	// Right Left Case.
	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rotateRight(node->right);
		recordSnapshot(snapshot, "rotateRL", node);
		node = rotateLeft(node);
		recordSnapshot(snapshot, "rotateLL", node);
		return node;
	}
	return node;
}
AVLTree::Node* AVLTree::replaceSnapshots(Node*& remove, Node*& node, std::vector<TreeSnapshot>& snapshot)
{
	recordSnapshot(snapshot, "find", node);
	if (node->left != nullptr)
		node->left = replaceSnapshots(remove, node->left, snapshot);
	else
	{
		Node* temp = node;
		remove->value = node->value;
		node = node->right;

		if (node != nullptr)
		{
			node->height = std::max(height(node->left), height(node->right)) + 1;
		}
		delete temp;
		recordSnapshot(snapshot, "replace", remove);
		return node;
	}
	node->height = std::max(height(node->left), height(node->right)) + 1;

	int balance = getBalance(node);
	recordSnapshot(snapshot, "check" + std::to_string(balance), node);
	if (balance > 1 && getBalance(node->left) >= 0) {
		node = rotateRight(node);
		recordSnapshot(snapshot, "rotateRR", node);
		return node;
	}
	// Left Right Case.
	if (balance > 1 && getBalance(node->left) < 0) {
		node->left = rotateLeft(node->left);
		recordSnapshot(snapshot, "rotateLR", node);
		node = rotateRight(node);
		recordSnapshot(snapshot, "rotateRR", node);
		return node;
	}
	// Right Right Case.
	if (balance < -1 && getBalance(node->right) <= 0) {
		int value = node->value;
		node = rotateLeft(node);
		recordSnapshot(snapshot, "rotateLL", node);
		return node;
	}
	// Right Left Case.
	if (balance < -1 && getBalance(node->right) > 0) {
		node->right = rotateRight(node->right);
		recordSnapshot(snapshot, "rotateRL", node);
		node = rotateLeft(node);
		recordSnapshot(snapshot, "rotateLL", node);
		return node;
	}
	return node;

	return node;

}

void AVLTree::recordInorder(Node* node, std::vector<int>& elements)
{
	if (node == nullptr)
		return;
	elements.push_back(node->order);
	recordInorder(node->left, elements);
	elements.push_back(node->order);
	recordInorder(node->right, elements);
}

AVLTree::Node* AVLTree::remove(Node* node, int value)
{
	if (node == nullptr)
	{
		return node;
	}
	if (value < node->value)
	{
		node->left = remove(node->left, value);
	}
	else if (value > node->value)
	{
		node->right = remove(node->right, value);
	}
	else
	{
		if (node->left == nullptr || node->right == nullptr)
		{
			Node* temp = node->left ? node->left : node->right;
			if (temp == nullptr)
			{
				temp = node;
				node = nullptr;
			}
			else
			{
				*node = *temp;
			}
			delete temp;
		}
		else
		{
			Node* temp = minValueNode(node->right);
			node->value = temp->value;
			node->right = remove(node->right, temp->value);
		}
	}
	if (node == nullptr)
	{
		return node;
	}
	return balance(node, value);
}
AVLTree::Node* AVLTree::search(Node* node, int value)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	if (value < node->value)
	{
		return search(node->left, value);
	}
	else if (value > node->value)
	{
		return search(node->right, value);
	}
	else
	{
		return node;
	}
}

AVLTree::Node* AVLTree::create(Node* node, std::vector<int> elements)
{
	for (int element : elements)
		node = insert(node, element);

	return node;
}

void AVLTree::clear(Node* node)
{
	if (node != nullptr)
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
}

AVLTree::Node* AVLTree::rotateRight(Node* node)
{
	Node* left = node->left;
	Node* right = left->right;
	left->right = node;
	node->left = right;
	node->height = std::max(height(node->left), height(node->right)) + 1;
	left->height = std::max(height(left->left), height(left->right)) + 1;


	return left;
}

AVLTree::Node* AVLTree::rotateLeft(Node* node)
{
	Node* right = node->right;
	Node* left = right->left;
	right->left = node;
	node->right = left;
	node->height = std::max(height(node->left), height(node->right)) + 1;
	right->height = std::max(height(right->left), height(right->right)) + 1;

	return right;
}

AVLTree::Node* AVLTree::balance(Node* node, int key)
{
	if (node == nullptr)
	{
		return node;
	}
	int balance = getBalance(node);

	if (balance > 1)
	{
		if (key > node->left->value)
		{
			node->left = rotateLeft(node->left);
		}
		return rotateRight(node);
	}
	if (balance < -1)
	{
		if (key < node->right->value)
		{
			node->right = rotateRight(node->right);
		}
		return rotateLeft(node);
	}
	return node;
}

int AVLTree::height(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	return node->height;
}

int AVLTree::getBalance(Node* node)
{
	if (node == nullptr)
	{
		return 0;
	}
	return height(node->left) - height(node->right);
}

AVLTree::Node* AVLTree::minValueNode(Node* node)
{
	Node* current = node;
	while (current->left != nullptr)
	{
		current = current->left;
	}
	return current;
}

AVLTree::Node* AVLTree::maxValueNode(Node* node)
{
	Node* current = node;
	while (current->right != nullptr)
	{
		current = current->right;
	}
	return current;
}

void AVLTree::reorder(Node* node, int& order)
{
	if (node == nullptr)
		return;

	reorder(node->left, order);
	node->order = order;
	order++;
	reorder(node->right, order);
}

void AVLTree::reorderDepth(Node* node, int depth)
{
	if (node == nullptr)
		return;
	reorderDepth(node->left, depth + 1);
	node->depth = depth;
	reorderDepth(node->right, depth + 1);
}

void AVLTree::inorder(Node* node, std::vector<int>& elements)
{
	if (node == nullptr)
	{
		return;
	}
	inorder(node->left, elements);
	elements.push_back(node->value);
	inorder(node->right, elements);
}

void AVLTree::inorderDepth(Node* node, int depth, std::vector<int>& elements)
{
	if (node == nullptr)
	{
		return;
	}
	inorderDepth(node->left, depth + 1, elements);
	elements.push_back(depth);
	inorderDepth(node->right, depth + 1, elements);
}

void AVLTree::inorderParent(Node* node, Node* parr, std::vector<int>& elements)
{
	if (node == nullptr)
	{
		return;
	}
	inorderParent(node->left, node, elements);
	if (parr != nullptr)
		elements.push_back(parr->order);
	else
		elements.push_back(-1);
	inorderParent(node->right, node, elements);
}

void AVLTree::inorderHeight(Node* node, std::vector<int>& elements)

{
	if (node == nullptr)
	{
		return;
	}
	inorderHeight(node->left, elements);
	elements.push_back(node->height);
	inorderHeight(node->right, elements);
}

void AVLTree::recordSnapshot(std::vector<TreeSnapshot>& snapshots, std::string operation, Node* x)
{
	TreeSnapshot snapshot;
	snapshot.inorder.clear();
	snapshot.inorderDepth.clear();
	snapshot.parent.clear();
	snapshot.height.clear();
	int order = 0;
	reorder(root, order);
	inorder(root, snapshot.inorder);
	inorderDepth(root, 0, snapshot.inorderDepth);
	inorderParent(root, nullptr, snapshot.parent);
	inorderHeight(root, snapshot.height);
	snapshot.operation = operation;
	snapshot.order = x->order;
	snapshots.push_back(snapshot);
}
