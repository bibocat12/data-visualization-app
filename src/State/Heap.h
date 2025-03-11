#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

class MinHeap
{
private:
	int capacity;
	int* harr;
	int size;

public:
	MinHeap(int cap);
	~MinHeap();
	int parent(int i);
	int left(int i);
	int right(int i);
	int Size();
	int depth(int i);

	void minHeapify(int i);
	std::vector<std::pair<int, int>> insertKey(int value);
	void deleteKey(int i);
	int getMin();
	void extractMin();
	void decreaseKey(int i, int newValue);
	void update(int i, int newValue);
	std::vector<int> getAllElements();
	void removeAll();
};

