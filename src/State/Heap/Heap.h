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

	std::vector<std::pair<int, int>> minHeapify(int i);
	std::vector<std::pair<int, int>> insertKey(int value);
	std::vector<std::vector<std::pair<int, int>>> deleteKey(int i);
	int getMin();
	std::vector<std::pair<int, int>> extractMin();
	std::vector<std::pair<int, int>> decreaseKey(int i);
	std::vector<std::pair<int, int>> update(int i, int newValue);
	std::vector<int> getAllElements();
	void removeAll();
	bool isLessThanParent(int i, int value);
	std::vector<std::vector<std::pair<int, int>>> create(std::vector<int> nums);
};

