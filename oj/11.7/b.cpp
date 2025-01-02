#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <class T>
class UnionFind {
    /* 并查集类 */
public:
    UnionFind<T>(int n) { 
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
    int m, n;
    cin >> m >> n;
    UnionFind<int> uf(m);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        uf.merge(a, b);
    }

    set<int> roots;
    for (int i = 1; i <= m; i++) {
        roots.insert(uf.find(i));
    }
    cout << roots.size() - 1 << endl;
    return 0;
}