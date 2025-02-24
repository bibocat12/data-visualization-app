#pragma once

#include <vector>

class SinglyLinkedList
{
public:
	SinglyLinkedList();
	~SinglyLinkedList();


	void init(std::vector<int> allElements);
	void insert(int element);
	void deleteElement(int element);
	int search(int element);
	void removeAll();
	
	int getSize();
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

