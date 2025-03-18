#include "Graph.h"

void Graph::addEdge(int u, int v, int weight, bool isDirected)
{
	edges.push_back({ u, v, weight, isDirected});
	c[u][v] = weight;
	if (!isDirected) c[v][u] = weight;
}

void Graph::reset()
{
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) c[i][j] = -1;
	}
	edges.clear();
}

bool Graph::hasEdge(int u, int v)
{
	return c[u][v] != -1;
}
