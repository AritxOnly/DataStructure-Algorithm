#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int longestCycle(vector<int>& edges) {
    int n = edges.size();
    vector<int> visited(n, 0); // 0: 未访问, >0: 已访问
    int maxLength = -1;
    int time = 1; // 时间戳

    for (int i = 0; i < n; ++i) {
        if (visited[i] == 0) {
            int current = i;
            unordered_map<int, int> visit_time; // 记录节点访问的时间戳

            while (current != -1 && visited[current] == 0) {
                visited[current] = time;
                visit_time[current] = time;
                time++;
                current = edges[current];
            }

            if (current != -1 && visit_time.count(current)) {
                // 找到一个环
                int length = time - visit_time[current];
                if (length > maxLength) {
                    maxLength = length;
                }
            }
        }
    }

    return maxLength;
}

int main() {
    int n;
    cin >> n;
    vector<int> edges(n);
    for (int i = 0; i < n; ++i) {
        cin >> edges[i];
    }

    int result = longestCycle(edges);
    cout << result << endl;

    return 0;
}