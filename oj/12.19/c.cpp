#include <iostream>
#include <unordered_map>
#include <stack>
#include <vector>

using namespace std;

class Graph {
    using Edges = unordered_map<int, int>;
    using AdjTable = vector<Edges>; // bool代表是否沉没

public:
    Graph(int n) : adj(n), sinked(n) {}
    ~Graph() = default;

    void insert(int from, int to) {
        /* 无向边插入 */
        adj[from][to] = 1;
        adj[to][from] = 1;
    }

    void sink(int vex) {
//        adj[vex].first.clear();
        sinked[vex] = true; // 标记为已沉没
    }

    int count() {
        /* 统计连通的岛屿个数 */
        int n = adj.size();
        vector<bool> visited(n, false);
        int islandCount = 0;

        for(int i = 0; i < n; ++i) {
            // 如果顶点没有被沉没且未被访问过
            if(!sinked[i] && !visited[i]) {
                islandCount++;
                // 使用栈进行DFS遍历
                stack<int> s;
                s.push(i);
                visited[i] = true;

                while(!s.empty()) {
                    int current = s.top();
                    s.pop();

                    for(const auto& neighbor : adj[current]) {
                        if(!sinked[neighbor.first] && !visited[neighbor.first]) {
                            visited[neighbor.first] = true;
                            s.push(neighbor.first);
                        }
                    }
                }
            }
        }

        return islandCount;
    }

private:
    AdjTable adj;   // 邻接表
    vector<bool> sinked;    // 标记是否沉没
};

#define connect insert

int main() {
    int n, m;
    cin >> n >> m;
    Graph bridges(n);

    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        bridges.connect(u, v);
    }

    printf("%d\n", bridges.count());
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int tmp;
        cin >> tmp;
        bridges.sink(tmp);
        printf("%d\n", bridges.count());
    }

    return 0;
}