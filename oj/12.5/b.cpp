#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Graph {
    using Edges = unordered_map<int, int>;
    using EdgeTable = vector<Edges>;

    const int INF = 10000000;

public:
    Graph(int n) : vexs(n + 1), n(n) {}
    ~Graph() = default;

    void insert(int from, int end, int w) {
        vexs[from][end] = w;
    }

    void insert(pair<int, int> e, int w) {
        vexs[e.first][e.second] = w;
    }

    vector<int> singleSourceAllShortestPath(int src) {
        // 单源点最短路径
        set<int> s; // 集合S
        vector<int> dist(n + 1, INF);
        auto f = [&dist, &s, this]() -> pair<int,int> {
            // 找到当前dist数组中的最小且未访问过的元素
            int nn = (int)dist.size() - 1;
            int minIdx = -1;
            int minV = INF;

            for (int i = 1; i <= nn; i++) {
                if (s.find(i) == s.end() && dist[i] < minV) {
                    minV = dist[i];
                    minIdx = i;
                }
            }

            return {minIdx, minV};
        };

        dist[src] = 0;
        while (true) {
            auto v = f();
            int idx = v.first;
            int d = v.second;
            if (idx == -1) break; // 找不到未访问的可达节点
            s.insert(idx);

            // 松弛操作
            for (auto &each : vexs[idx]) {
                int to = each.first;
                int w = each.second;
                if (dist[idx] + w < dist[to]) {
                    dist[to] = dist[idx] + w;
                }
            }
        }

        return dist;
    }

private:
    EdgeTable vexs;
    int n;
};

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.insert(u, v, w);
    }

    auto dist = g.singleSourceAllShortestPath(s);

    // dist[0]未使用，从1开始
    const int INF = 10000000;
    int maxTime = -1;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INF) {
            // 说明有节点不可达
            cout << -1 << "\n";
            return 0;
        } else {
            if (dist[i] > maxTime) {
                maxTime = dist[i];
            }
        }
    }

    cout << maxTime << "\n";

    return 0;
}