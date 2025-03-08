#pragma once

#include <vector>

class SinglyLinkedList
{
public:
	SinglyLinkedList();
	~SinglyLinkedList();


	void init(std::vector<int> allElements);
	void insert(int element);
	void insert(int k, int v);
	void deleteElement(int element);
	int search(int element);
	void removeAll();
	
	int getSize();
	void update(int oldV, int newV);
	std::vector<int> getAllElements();
private:
	struct Node {
		int data;
		Node* next;
	};
	Node* head;
	int size;
	std::vector<int> allElements;

};

