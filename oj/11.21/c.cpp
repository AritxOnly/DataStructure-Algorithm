#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <class T>
class UnionFind {
    /* 并查集类 */
public:
    explicit UnionFind<T>(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;
    }

    int find(int x) {
        /* 查找x的根节点 */
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void merge(int x, int y) {
        /* 合并x和y所在的集合 */
        int root_x = find(x);
        int root_y = find(y);
        if (root_x != root_y)
            parent[root_x] = root_y;
    }

private:
    vector<T> parent; // 父节点数组
};

int main() {
    int n, m;
    cin >> n >> m;
    UnionFind<int> uf(n);
    vector<pair<int, vector<pair<int, int>>>>inputs;
    int total = 0;
    for (int i = 0; i < m; i++) {
        int x, y, day;
        cin >> x >> y >> day;
        auto it = inputs.begin();
        for (; it != inputs.end(); it++) {
            if (it->first == day) break;   /* day exists */
        }
        if (it == inputs.end()) {
            inputs.push_back({day, vector<pair<int, int>>()});
            inputs[total].second.push_back({x, y});
            total++;
        } else {
            it->second.push_back({x, y});
        }
    }
    int first;
    cin >> first;
    uf.merge(0, first);

    auto f = [](pair<int, vector<pair<int, int>>>f, pair<int, vector<pair<int, int>>>s) -> bool {
        return f.first < s.first;
    };

    sort(inputs.begin(), inputs.end(), f);
    for (const auto& incident : inputs) {
        auto v = incident.second;
        for (const auto& p : v) {
            uf.merge(p.first, p.second);
        }
    }

    int pa_0 = uf.find(0);
    cout << 0 << " ";
    for (int i = 1; i < n; i++) {
        if (uf.find(i) == pa_0)
            cout << i << " ";
    }

    return 0;
}