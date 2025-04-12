#pragma once

#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <array>

class Dsu {
private:
    std::vector<int> p;
public:
    void init();
    void clear();
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
    std::vector<std::vector<int>> c;

public:
    void init();
    void setDirected(int directed);
    void addEdge(int u, int v, int weight = 0, bool isDirected = false);
    void reset();
    bool hasEdge(int u, int v);
    std::vector<std::pair<int, bool>> kruskal();
    std::vector<std::array<int, 3>> dijkstra(int source, int n);
};
