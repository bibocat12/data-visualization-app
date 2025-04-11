#include "../../../header/State/Heap/Heap.h"

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
	if (i == 0) return 0;
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

std::vector<std::pair<int, int>> MinHeap::minHeapify(int i)
{
	std::vector<std::pair<int, int>> res;
	res.push_back({ i, harr[i] });
	while (1) {
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
			res.push_back({ minPos, harr[minPos] });
			std::swap(harr[minPos], harr[i]);
			i = minPos;
			res.push_back({ i, harr[i] });
		}
		else break;
	}
	return res;
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

std::vector<std::vector<std::pair<int, int>>> MinHeap::deleteKey(int i)
{
	std::vector<std::vector<std::pair<int, int>>> res;
	res.push_back(decreaseKey(i));
	res.push_back(extractMin());
	return res;
}

int MinHeap::getMin()
{
	if (size == 0) {
		std::cerr << "Heap is empty\n";
	}
	return harr[0];
}

std::vector<std::pair<int, int>> MinHeap::extractMin()
{
	harr[0] = harr[size - 1];
	size--;
	return minHeapify(0);
}

std::vector<std::pair<int, int>> MinHeap::decreaseKey(int i)
{
	std::vector<std::pair<int, int>> res;
	res.push_back({ i, harr[i] });
	while (i) {
		res.push_back({ parent(i), harr[parent(i)] });
		std::swap(harr[i], harr[parent(i)]);
		i = parent(i);
	}
	return res;
}

std::vector<std::pair<int, int>> MinHeap::update(int i, int newValue)
{
	std::vector<std::pair<int, int>> res;
	harr[i] = newValue;
	if (i > 0 && harr[i] <= harr[parent(i)]) {
		res.push_back({ i, harr[i] });
		while (i && harr[i] < harr[parent(i)]) {
			res.push_back({ parent(i), harr[parent(i)] });
			std::swap(harr[i], harr[parent(i)]);
			i = parent(i);
		}
	}
	else res = minHeapify(i);
	return res;
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

bool MinHeap::isLessThanParent(int i, int value)
{
	return i > 0 && value <= harr[parent(i)];
}

std::vector<std::vector<std::pair<int, int>>> MinHeap::create(std::vector<int> nums)
{
	size = 0;
	std::vector<std::vector<std::pair<int, int>>> res;
	std::vector<std::pair<int, int>> tmp;
	for (int i = 0; i < (int)nums.size(); i++) {
		harr[size++] = nums[i];
		tmp.push_back({ i, nums[i] });
	}
	res.push_back(tmp);

	for (int i = (int)nums.size() / 2 - 1; i >= 0; i--) {
		res.push_back(minHeapify(i));
	}
	return res;
}