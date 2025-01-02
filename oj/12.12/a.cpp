#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <climits>
#include <queue>

using namespace std;

class Graph {
    using Edges = unordered_map<int, int>;
    using StartVexs = vector<Edges>;

    const int INF = INT_MAX;

public:
    Graph(int n) : vexs(n) {}

    void insert(int from, int to, int w) {
        vexs[from][to] = w;
        // 有向图
    }

    int shortestPathWithRestriction(int src, int dst, int k) {
        int n = vexs.size();
        vector<vector<int>> dist(n, vector<int>(k + 1, INF));
        set<pair<int, int>> visited;
        dist[src][0] = 0;

        auto f = [&]() -> pair<int, int> {
            int minNode = -1;
            int minE = -1;
            int minV = INF;

            // O(n*K)搜索，效率低，仅为演示
            for (int i = 0; i < n; i++) {
                for (int e = 0; e <= k; e++) {
                    if (dist[i][e] < minV && visited.find({i,e}) == visited.end()) {
                        minV = dist[i][e];
                        minNode = i;
                        minE = e;
                    }
                }
            }
            return {minNode, minE};
        };
        // 总状态数是 n*(K+1)
        for (int _ = 0; _ < (n * (k + 1)); _++) {
            auto p = f();
            int node = p.first;
            int usedE = p.second;
            if (node == -1) {
                // 无可选状态
                break;
            }

            visited.insert({node, usedE});
            if (node == dst) {
                // 一旦找到到达dst的任意条数边的最优值，即可返回
                return dist[node][usedE];
            }

            // 从 node 出发的边，尝试增加一条边到达下一个节点
            for (auto &each : vexs[node]) {
                int to = each.first;
                int w = each.second;
                if (usedE < k) { // 只有在使用的边数小于K时才能再走一条边
                    int newDist = dist[node][usedE] + w;
                    if (newDist < dist[to][usedE + 1]) {
                        dist[to][usedE + 1] = newDist;
                    }
                }
            }
        }

        int ans = INF;
        for (int e = 0; e <= k; e++) {
            ans = min(ans, dist[dst][e]);
        }

        return ans == INF ? -1 : ans;
    }

private:
    StartVexs vexs;
};

int main() {
    int school, home, k;
    cin >> school >> home >> k;
    int n, m;
    cin >> n >> m;
    Graph railway(n);
    for (int _ = 0; _ < m; _++) {
        int src, dst, price;
        cin >> src >> dst >> price;
        railway.insert(src, dst, price);
    }
    cout << railway.shortestPathWithRestriction(school, home, k + 1);
    return 0;
}