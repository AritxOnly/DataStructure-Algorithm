#include <iostream>

const int MAXN = 1005;

int mtrx[MAXN][MAXN], map[MAXN][MAXN];

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mtrx[i][j];
            map[i][j] = (mtrx[i][j] == 0) ? 0 : 1;
        }
    }
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < m; j++) {
            cnt += (mtrx[i][j] == 0) ? 1 : 0;
        }
        if (cnt % 2 == 1) {
            for (int j = 0; j < m; j++) {
                map[i][j] = 0;
            }
        }
    }

    for (int j = 0; j < m; j++) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += (mtrx[i][j] == 0) ? 1 : 0;
        }
        if (cnt % 2 == 1) {
            for (int i = 0; i < n; i++) {
                map[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ((map[i][j] == 0) ? 0 : mtrx[i][j]) << " ";
        }
        cout << "\n";
    }
    return 0;
}