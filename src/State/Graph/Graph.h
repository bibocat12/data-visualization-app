#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <array>

class Dsu {
private:
    static const int maxn = 100 + 7;
    int p[maxn];
public:
    void init();
    int find_node(int u);
    bool Union(int u, int v);
};

class Graph {
public:
    struct edge {
        int u, v, weight;
        bool isDirected;

        friend bool operator < (edge a, edge b) {
            return a.weight < b.weight;
        }
    };

    std::vector<edge> edges;
    Dsu ds;
    static const int maxn = 107;
    int c[maxn][maxn];

public:
    void setDirected(int directed);
    void addEdge(int u, int v, int weight = 0, bool isDirected = false);
    void reset();
    bool hasEdge(int u, int v);
    std::vector<std::pair<int, bool>> kruskal();
    std::vector<std::array<int, 3>> dijkstra(int source, int n);
};
