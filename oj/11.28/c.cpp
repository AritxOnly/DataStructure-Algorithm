#include <iostream>
#include <vector>

using namespace std;

int main() {
    /* 思路：二分查找 */
    int n, m;
    cin >> n >> m;
    vector<long long> h(n);
    long long maxh = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        if (h[i] > maxh) {
            maxh = h[i];
        }
    }

    long long l = 0, r = maxh;
    long long ans = -1;

    while (l <= r) {
        long long mid = (l + r) / 2;
        long long total_remaining = 0;
        for (int i = 0; i < n; ++i) {
            total_remaining += std::max(0LL, h[i] - mid);
        }

        if (total_remaining >= m) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << ans << endl;

    return 0;
}