#include <iostream>

using namespace std;

int n;
char seq[16];
char target[16];
char _stack[16];
char _seq[16];
int ptr = -1;

int dfs(int i, int remain, bool pop);

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> seq[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> target[i];
    }
    int cnt = dfs(0, 0, false);
    cout << cnt / 2;
    return 0;
}

int dfs(int i, int remain, bool pop) {
    // 递归结束条件？
    if (i == n && remain == 0) {
        return (_seq[n - 1] == target[n - 1]);
    }
    if (pop && remain == 0) {
        return 0;
    }

    int total = 0;
    if (pop) {
        int temp = _stack[--remain];
        _seq[++ptr] = _stack[remain]; // 出栈
        if (_seq[ptr] != target[ptr]) {
            remain++;
            ptr--;
            return 0;
        }
        total += dfs(i, remain, true);
        total += dfs(i, remain, false);
        _stack[remain++] = temp;    // 恢复栈状态
        ptr--;
    } else {
        if (i >= n) {
            return 0;
        }
        _stack[remain++] = seq[i];
        total += dfs(i + 1, remain, true);
        total += dfs(i + 1, remain, false);
        remain--;
    }
    return total;
}