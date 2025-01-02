#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(vector<int>& e) : edges(e) {}

    ~Graph() = default;

    int getCircle(int vex) {
        int cnt = 0;
        int org = vex;
        while (cnt <= edges.size()) {
            vex = edges[vex];
            cnt++;
            if (vex == org)
                break;
        }
        return (cnt > edges.size()) ? -1 : cnt;
    }

    int maximumCircle() {
        int max = -1;
        for (const auto& v : edges) {
            max = std::max(getCircle(v), max);
        }
        return max;
    }

private:
    vector<int> edges;
};

int main() {
    int n;
    cin >> n;
    vector<int> e(n);
    for (int i = 0; i < n; i++) {
        cin >> e[i];
    }
    Graph g(e);
    cout << g.maximumCircle();
    return 0;
}