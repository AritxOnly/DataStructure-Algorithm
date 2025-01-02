#include <iostream>
#include <string>

using namespace std;

const int MAXN = 100005;

bool find(string& pat, string& text) {
    // 用KMP算法匹配字符串
    // *为通配符
    int len = pat.length();
    int size = text.length();
    int* next = new int[len];
    auto get_next = [&]() {
        int j = 0, k = -1;
        next[0] = -1;
        j = 1;
        while (j < len) {
            k = next[j - 1];
            while (true) {
                if (k == -1 || pat[j - 1] == pat[k] || pat[j - 1] == '*' || pat[k] == '*') {
                    k++;
                    next[j] = k;
                    j++;
                    break;
                }
                k = next[k];
            }
        }
    };
    get_next();
    int p = 0, t = 0;
    while (p < len && t < size) {
        if (p == -1 || pat[p] == text[t] || pat[p] == '*') {
            p++;
            t++;
        } else {
            p = next[p];
        }
    }
    if (p < len)
        return false;
    return true;
}

int main() {
    int n;
    cin >> n;
    string pat;
    cin >> pat;
    string text;
    for (int i = 0; i < n; i++) {
        cin >> text;
        cout << (find(pat, text) ? "true" : "false") << endl;
    }
    return 0;
}