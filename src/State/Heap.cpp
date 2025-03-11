#include "Heap.h"

MinHeap::MinHeap(int cap)
{
	capacity = cap;
	harr = new int[cap];
	size = 0;
}

MinHeap::~MinHeap()
{
	size = 0;
	capacity = 0;
	delete[] harr;
}

int MinHeap::parent(int i)
{
	return (i - 1) / 2;
}

int MinHeap::left(int i)
{
	return i * 2 + 1;
}

int MinHeap::right(int i)
{
	return i * 2 + 2;
}

int MinHeap::Size()
{
	return size;
}

int MinHeap::depth(int i)
{
	return log2(i + 1);
}

void MinHeap::minHeapify(int i)
{
	int leftChild = left(i);
	int rightChild = right(i);
	int minPos = i;

	if (leftChild < size && harr[minPos] > harr[leftChild]) {
		minPos = leftChild;
	}
	if (rightChild < size && harr[minPos] > harr[rightChild]) {
		minPos = rightChild;
	}
	if (minPos != i) {
		std::swap(harr[minPos], harr[i]);
	}
}

std::vector<std::pair<int, int>> MinHeap::insertKey(int value)
{
	/*if (size == capacity) {
		std::cerr << "\nOverflow: Could not insertKey\n";
		return;
	}*/

	std::vector<std::pair<int, int>> res;
	size++;
	harr[size - 1] = value;
	int i = size - 1;
	res.push_back({ i, harr[i] });
	while (i && harr[i] < harr[parent(i)]) {
		res.push_back({parent(i), harr[parent(i)]});
		std::swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
	return res;
}

void MinHeap::deleteKey(int i)
{
	decreaseKey(i, INT_MIN);
	extractMin();
}

int MinHeap::getMin()
{
	if (size == 0) {
		std::cerr << "Heap is empty\n";
	}
	return harr[0];
}

void MinHeap::extractMin()
{
	harr[0] = harr[size - 1];
	size--;
	minHeapify(0);
}

void MinHeap::decreaseKey(int i, int newValue)
{
	harr[i] = newValue;
	while (i && harr[i] < harr[parent(i)]) {
		std::swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
}

void MinHeap::update(int i, int newValue)
{
	harr[i] = newValue;
	while (i && harr[i] < harr[parent(i)]) {
		std::swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
	minHeapify(i);
}

std::vector<int> MinHeap::getAllElements()
{
	std::vector<int> res;
	for (int i = 0; i < size; i++) res.push_back(harr[i]);
	return res;
}

void MinHeap::removeAll()
{
	while (size) {
		extractMin();
	}
}
