#include "../../../header/State/Graph/Graph.h"

void Dsu::init() {
    for (int i = 0; i < maxn; i++) {
        p[i] = -1;
    }
}

int Dsu::find_node(int u) {
    return p[u] < 0 ? u : p[u] = find_node(p[u]);
}

bool Dsu::Union(int u, int v) {
    u = find_node(u);
    v = find_node(v);
    if (u == v) return false;
    if (p[u] > p[v]) std::swap(u, v);
    p[u] += p[v];
    p[v] = u;
    return true;
}

void Graph::setDirected(int directed)
{
    for (auto& edge : edges) {
        edge.isDirected = directed;
    }
}

void Graph::addEdge(int u, int v, int weight, bool isDirected) {
    edges.push_back({ u, v, weight, isDirected });
    c[u][v] = weight;
    if (!isDirected) c[v][u] = weight;
}

void Graph::reset() {
    edges.clear();
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++) {
            c[i][j] = 0;
        }
    }
    ds.init();
}

bool Graph::hasEdge(int u, int v) {
    return c[u][v] != 0;
}

std::vector<std::pair<int, bool>> Graph::kruskal() {
    ds.init();
    std::vector<int> id(edges.size());
    for (int i = 0; i < (int)id.size(); i++) {
        id[i] = i;
    }

    std::sort(id.begin(), id.end(), [&](int i, int j) {
        return edges[i] < edges[j];
        });

    std::vector<std::pair<int, bool>> ans;
    for (int i : id) {
        ans.push_back({ i, ds.Union(edges[i].u, edges[i].v) });
    }
    return ans;
}

std::vector<std::array<int, 3>> Graph::dijkstra(int source, int n)
{
    int oo = (int)1e9 + 7;
    std::vector<int> f(n + 1, oo);
    std::vector<std::array<int, 3>> res;

    f[source] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.push({ 0, source });
    res.push_back({ -1, source, 0 });

    while (!q.empty()) {
        int fu = q.top().first;
        int u = q.top().second;
        q.pop();

        if (fu != f[u]) continue;

        for (int i = 0; i < (int)edges.size(); i++) {
            auto edge = edges[i];
            if (edge.u != u && edge.v != u) continue;
            if (edge.isDirected && edge.u != u) continue;
            int v = (edge.u ^ edge.v ^ u);
            if (f[v] > fu + edge.weight) {
                f[v] = fu + edge.weight;
                q.push({ f[v], v });
                res.push_back({ i, v, f[v] });
            }
        }
    }
    return res;
}
