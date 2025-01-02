#include <iostream>
#include <queue>

using namespace std;

long long findK_th(int k, priority_queue<long long>& q) {
    vector<long long>v;
    for (int i = 0; i < k; i++) {
        v.push_back(q.top());
        q.pop();
    }
    long long ans = v.back();
    for (int i = 0; i < k; i++) {
        long long tmp = v.back();
        q.push(tmp);
        v.pop_back();
    }
    return ans;
}

int main() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<long long>init(m);
    for (int i = 0; i < m; i++) {
        cin >> init[i];
    }
    priority_queue<long long>reelImpacts(init.begin(), init.end());
    long long ans = findK_th(k, reelImpacts);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        reelImpacts.push(tmp);
        ans += findK_th(k, reelImpacts);
    }
    cout << ans;
}