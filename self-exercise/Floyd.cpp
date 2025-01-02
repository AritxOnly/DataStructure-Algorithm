#include <climits>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace std;

class graph {
    using Vex = pair<int, int>;
    const int INF = INT_MAX;

public:
    graph(int n = -1) : vexs(map<int, vector<Vex>*>()), nums(n) {}

    ~graph() {
        for (auto each : vexs) {
            delete each.second;
        }
    }

    void insert_edge(int from, int to, int w) {
        vector<Vex>* v;
        if (vexs.contains(from)) {
            v = vexs[from];
        } else {
            v = new vector<Vex>;
            vexs[from] = v;
        }
        v->push_back({to, w});
    }

    vector<vector<int>> floyd() {
        set<int> nodes;
        int N = (nums != -1) ? nums : nodes.size();
        if (N != 0) goto calculate;

        for (const auto& p : vexs) {
            nodes.insert(p.first);
            vector<Vex>* edges = p.second;
            for (const auto& vex : *edges) {
                nodes.insert(vex.first);
            }
        }
    
    calculate:
        vector<vector<int>> dist(N, vector<int>(N, INF));
        
        // 初始化
        for (int i = 0; i < N; i++) {
            dist[i][i] = 0; // 自己到自己的距离为0
            vector<Vex>* edges = vexs[i];
            for (const auto& vex : *edges) {
                dist[i][vex.first] = vex.second;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        return dist;
    }

private:
    map<int, vector<Vex>*> vexs;
    int nums;
};

int main() {
    int n, m;
    cin >> n >> m;
    graph g(n);
    for (int i = 0; i < m; i++) {
        int f, t, w;
        cin >> f >> t >> w;
        g.insert_edge(f, t, w);
    }
    vector<vector<int>> v = g.floyd();
    for (const auto& line : v) {
        for (const auto& elm : line) {
            cout << elm << " ";
        }
        cout << endl;
    }
    return 0;
}