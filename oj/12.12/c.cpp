#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

class Graph {
    using Edge = pair<int, int>; // (destination, weight)
    using Table = vector<unordered_map<int, int>>;

public:
    Graph(int n) : N(n), adj(n), tadj(n) {}
    ~Graph() = default;

    // 插入有向边及其权重
    void insert(int from, int to, int w) {
        adj[from][to] = w;
        tadj[to][from] = w;
    }

    // 计算关键路径，返回关键边的列表
    vector<pair<int, int>> criticalPath() {
        vector<int> topoOrder;
        if (!topologicalSort(topoOrder)) {
            // 如果图中存在环，则无法进行关键路径分析
            return {};
        }

        // 前向遍历，计算最早发生时间（EE）
        vector<int> EE(N, 0);
        for (int u : topoOrder) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (EE[v] < EE[u] + w) {
                    EE[v] = EE[u] + w;
                }
            }
        }

        // 找到终点节点（最晚的EE值）
        int maxEE = 0;
        int endNode = 0;
        for (int u = 0; u < N; ++u) {
            if (EE[u] > maxEE) {
                maxEE = EE[u];
                endNode = u;
            }
        }

        // 后向遍历，计算最晚发生时间（LE）
        vector<int> LE(N, numeric_limits<int>::max());
        LE[endNode] = EE[endNode];
        for (int i = topoOrder.size() - 1; i >= 0; --i) {
            int u = topoOrder[i];
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (LE[u] > LE[v] - w) {
                    LE[u] = LE[v] - w;
                }
            }
        }

        // 确定关键边：EE[u] + w(u, v) == EE[v] 且 LE[u] + w(u, v) == LE[v]
        // 且 EE[u] == LE[u] 且 EE[v] == LE[v]
        vector<pair<int, int>> criticalEdges;
        for (int u = 0; u < N; ++u) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                if (EE[u] + w == EE[v] && LE[u] + w == LE[v] && EE[u] == LE[u] && EE[v] == LE[v]) {
                    criticalEdges.emplace_back(u, v);
                }
            }
        }

        return criticalEdges;
    }

private:
    int N;
    Table adj;  // 原邻接表
    Table tadj; // 逆邻接表

    // 拓扑排序，返回是否成功（即图中是否有环）
    bool topologicalSort(vector<int>& topoOrder) {
        vector<int> inDegree(N, 0);
        for (int u = 0; u < N; ++u) {
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                inDegree[v]++;
            }
        }

        queue<int> q;
        for (int u = 0; u < N; ++u) {
            if (inDegree[u] == 0) {
                q.push(u);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            for (const auto& edge : adj[u]) {
                int v = edge.first;
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        return (topoOrder.size() == N);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, e;
    cin >> n >> e;
    Graph g(n);
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.insert(u, v, w);
    }
    auto ans = g.criticalPath();
    sort(ans.begin(), ans.end(), [](const pair<int, int>& a, const pair<int, int>& b) -> bool {
        return (a.first == b.first) ? (a.second < b.second) : (a.first < b.first);
    });

    for (const auto& each : ans) {
        cout << each.first << " " << each.second << "\n";
    }
    return 0;
}