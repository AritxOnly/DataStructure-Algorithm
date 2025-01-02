#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Duration {
    int start;
    int end;
};

int main() {
    int n;
    cin >> n;
    vector<Duration> machine(n);
    int u, v;
    for (int i = 0; i < n; i++) {
        cin >> u >> v;
        machine[i] = {u, v};
    }

    // 按结束时间排序，如果结束时间相同，则按开始时间排序
    sort(machine.begin(), machine.end(), [](const Duration &a, const Duration &b) -> bool {
        if (a.end != b.end)
            return a.end < b.end;
        else
            return a.start < b.start;
    });

    int cnt = 0;
    int last_end_time = -1; // 初始化为一个比所有开始时间都小的值

    for (const auto &m : machine) {
        if (m.start >= last_end_time) {
            cnt++;
            last_end_time = m.end;
        }
    }

    cout << cnt;
    return 0;
}