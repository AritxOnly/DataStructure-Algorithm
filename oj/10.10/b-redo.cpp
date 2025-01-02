#include <iostream>

using namespace std;

const int MAXN = 2005;
int a[MAXN][MAXN], c[MAXN][MAXN];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int tmp;
            cin >> tmp;
        }
    }
}