#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

class Graph {
	struct edge {
		int u, v, weight, isDirected;
	};
	std::vector<edge> edges;

	static const int maxn = 107;
	int c[maxn][maxn];

public:
	void addEdge(int u, int v, int weight = 0, bool isDirected = false);
	void reset();
	bool hasEdge(int u, int v);
};