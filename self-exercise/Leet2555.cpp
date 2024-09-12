/**
 * Leetcode 2555. Maximize Win From Two Segments
 * https://leetcode.cn/problems/maximize-win-from-two-segments/
 * Solved with Solution: DP, time complexity: O(nlogn)
 */

#include <algorithm>
#include <cassert>
#include <vector>
#include <cstdio>

using std::vector;

class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int n = prizePositions.size();
        vector<int> dp(n + 1);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int j = std::lower_bound(prizePositions.begin(), prizePositions.end(), prizePositions[i] - k) - prizePositions.begin();
            ans = std::max(ans, dp[j] + i - j + 1);
            dp[i + 1] = std::max(dp[i], i - j + 1);
        }
        return ans;
    }
};

void testCase() {
    Solution sol;
    vector<int> case1 = {1, 1, 2, 2, 3, 3, 5};
    int k1 = 2;
    assert(sol.maximizeWin(case1, k1) == 7);
    printf("Testcase 1 Passed\n");
    vector<int> case2 = {1, 2, 3, 4};
    int k2 = 0;
    assert(sol.maximizeWin(case2, k2) == 2);
    printf("Testcase 2 Passed\n");
    printf("All cases passed\n");
}

int main() {
    testCase();
    return 0;
}