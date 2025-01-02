#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;

class Graph {
    using Table = unordered_map<int, vector<int>>;
    using Dfs = function<void (int, vector<int>&)>;

public:
    Graph(int n) : N(n) {}
    ~Graph() = default;

    void insert(int from, int to) {
        adj[from].push_back(to);
        tadj[to].push_back(from);
    }

    vector<int> solution() {
        vector<bool> visited(N);
        Dfs findOrder = [&](int u, vector<int>& order) {
            visited[u] = true;
            for (auto& v : adj[u]) {
                if (!visited[v])
                    findOrder(v, order);
            }
            order.push_back(u);
        };

        vector<int> seq;
        for (int u = 0; u < N; u++) {
            // 遍历点
            if (!visited[u])
                findOrder(u, seq);
        }

        fill(visited.begin(), visited.end(), false);
        Dfs findSCC = [&](int u, vector<int>& comp) {
            visited[u] = true;
            comp.push_back(u);
            for (auto& v : tadj[u]) {
                if (!visited[v])
                    findSCC(v, comp);
            }
        };

        vector<vector<int>> sccs;
        for (int i = seq.size() - 1; i >= 0; i--) {
            // 从最后被遍历到的点开始找
            int u = seq[i];
            if (!visited[u]) {
                vector<int> comp;
                findSCC(u, comp);
                sccs.push_back(comp);
            }
        }

        int max_size = 0;
        vector<int> result;
        for(auto &scc : sccs){
            if(scc.size() > max_size){
                max_size = scc.size();
                result = scc;
            }
            else if(scc.size() == max_size){
                vector<int> temp = scc;
                sort(temp.begin(), temp.end());
                vector<int> sorted_result = result;
                sort(sorted_result.begin(), sorted_result.end());
                if(temp < sorted_result){
                    result = scc;
                }
            }
        }

        // 排序输出
        sort(result.begin(), result.end());
        return result;
    }

private:
    int N;
    Table adj;  // 原邻接表
    Table tadj; // 转置邻接表
};

int main() {
    int m, n;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.insert(u, v);
    }
    auto res = g.solution();
    for (auto& ans : res) {
        cout << ans << " ";
    }
    return 0;
}