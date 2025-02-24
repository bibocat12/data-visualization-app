#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList()
{
	head = nullptr;
	size = 0;
}

SinglyLinkedList::~SinglyLinkedList()
{
}

void SinglyLinkedList::init(std::vector<int> allElements)
{
	removeAll();
	for (int i = 0; i < (int)allElements.size(); i++) {
		insert(allElements[i]);
	}
}

void SinglyLinkedList::insert(int element)
{
	Node* newNode = new Node();
	newNode->data = element;
	newNode->next = nullptr;
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
	size++;
}

void SinglyLinkedList::deleteElement(int element)
{
	Node* temp = head;
	Node* prev = nullptr;
	while (temp != nullptr && temp->data != element) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == nullptr) {
		return;
	}
	if (prev == nullptr) {
		head = temp->next;
	}
	else {
		prev->next = temp->next;
	}
	delete temp;
	size--;
}

int SinglyLinkedList::search(int element)
{
	Node* temp = head;
	int index = 0;
	while (temp != nullptr && temp->data != element) {
		temp = temp->next;
		index++;
	}
	if (temp == nullptr) {
		return -1;
	}
	return index;
}

void SinglyLinkedList::removeAll()
{
	Node* temp = head;
	while (temp != nullptr) {
		Node* next = temp->next;
		delete temp;
		temp = next;
	}
	head = nullptr;
	size = 0;
}

int SinglyLinkedList::getSize()
{
	return size;
}

std::vector<int> SinglyLinkedList::getAllElements()
{
	std::vector<int> allElements;
	Node* temp = head;
	while (temp != nullptr) {
		allElements.push_back(temp->data);
		temp = temp->next;
	}
	return allElements;
}

