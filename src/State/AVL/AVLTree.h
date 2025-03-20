#pragma once

#include <vector>
#include <iostream>
#include <queue>
#include <string>
class AVLTree
{
public:
	AVLTree();
	~AVLTree();

	void insert(int value);
	void remove(int value);
	void search(int value);
	std::vector<int> searchPath(int value);
	void create(std::vector<int> elements);
	std::vector<int> getAllElements();
	std::vector< int> getInorderDepth();
	std::vector<int> getParent();
	void clear();

	bool isParent(int value, int child);
	int countChild(int value);
	int findMinRight(int value);

	struct TreeSnapshot {
		std::string operation;
		int order;
		std::vector<int> inorder;
		std::vector<int> inorderDepth;
		std::vector<int> parent;
		std::vector<int> height;
	};

	std::vector<TreeSnapshot> insertSnapshots(int value);
	std::vector<TreeSnapshot> removeSnapshots(int value);
	std::vector<int> recordInorder();


private:
	struct Node
	{
		int value;
		Node* left;
		Node* right;
		int height;
		int order;
		int depth;
		Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}
	};
	Node* root;
	Node* insert(Node* node, int value);
	Node* insertSnapshot(Node*& node, int value, std::vector<TreeSnapshot>& snapshot);
	Node* removeSnapshot(Node*& node, int value, std::vector<TreeSnapshot>& snapshot);
	Node* replaceSnapshots(Node*& remove, Node*& node, std::vector<TreeSnapshot>& snapshot);
	void recordInorder(Node* node, std::vector<int>& elements);
	Node* remove(Node* node, int value);
	Node* search(Node* node, int value);

	Node* create(Node* node, std::vector<int> elements);
	void clear(Node* node);
	Node* rotateRight(Node* node);
	Node* rotateLeft(Node* node);
	Node* balance(Node* node, int key);
	int height(Node* node);
	int getBalance(Node* node);
	Node* minValueNode(Node* node);
	Node* maxValueNode(Node* node);
	void reorder(Node* node, int& order);
	void reorderDepth(Node* node, int depth);

	void inorder(Node* node, std::vector<int>& elements);
	void inorderDepth(Node* node, int depth, std::vector<int>& elements);
	void inorderParent(Node* node, Node* parr, std::vector<int>& elements);
	void inorderHeight(Node* node, std::vector<int>& elements);

	void recordSnapshot(std::vector<TreeSnapshot>& snapshots, std::string operation, Node* node);

};