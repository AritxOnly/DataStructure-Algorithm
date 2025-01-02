#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <limits>

using namespace std;

class Graph {
    using Edges = unordered_map<int, int>;
    using EdgeTable = vector<Edges>;

    const int INF = 1000000000; // 更大的INF

public:
    Graph(int n) : vexs(n + 1), n(n) {}

    void insert(int from, int end, int w) {
        vexs[from][end] = w;
        vexs[end][from] = w;
    }

    int solution(int src, int dst) {
        vector<int> dist(n + 1, INF);
        vector<bool> visited(n + 1, false);

        set<pair<int,int>> nodes;
        for (int i = 1; i <= n; i++) {
            nodes.insert({dist[i], i});
        }

        nodes.erase({dist[src], src});
        dist[src] = 0;
        nodes.insert({0, src});

        while(!nodes.empty()) {
            auto u = nodes.begin()->second;
            nodes.erase(nodes.begin());

            if (visited[u]) continue;
            visited[u] = true;

            if (u == dst) {
                return dist[u];
            }

            for (auto &edge : vexs[u]) {
                int v = edge.first;
                int w = edge.second;
                if (!visited[v]) {
                    int newDist = max(dist[u], w);
                    if (newDist < dist[v]) {
                        // 更新dist[v]并在set中调整位置
                        nodes.erase({dist[v], v});
                        dist[v] = newDist;
                        nodes.insert({dist[v], v});
                    }
                }
            }
        }

        return dist[dst] == INF ? -1 : dist[dst];
    }

private:
    EdgeTable vexs;
    int n;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.insert(u, v, w);
    }
    cout << g.solution(s, t);
    return 0;
}