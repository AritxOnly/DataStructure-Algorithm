/**
 * P1037 [NOIP2002 普及组] 产生数
 * https://www.luogu.com.cn/problem/P1037
 */

#include <cstring>
#include <iostream>

using namespace std;

typedef struct Transform {
    int from;
    int to;
} Transform;

string toStr(int n);

int main() {
    int n, k;
    Transform* trans = new Transform;
    for (int i = 0; i < k; i++)
        cin >> trans[i].from >> trans[i].to;
    string nStr = toStr(n);
    vector<int> canIndex;
    for (auto it = nStr.begin(); it != nStr.end(); ++it) {
        for (int i = 0; i < k; i++) {
            if (*it == trans[i].from) {
                canIndex.push_back(static_cast<int>(it - nStr.begin()));
                break;
            }
        }
    }

    for (const auto& index : canIndex) {
        
    }

    return 0;
}

string toStr(int n) {
    string res = "";
    while (n != 0) {
        int digit = n % 10;
        n /= 10;
        res += static_cast<char>(digit + '0');
    }
    string newRes;
    for (int i = res.size() - 1; i >= 0; i--) {
        newRes += res[i];
    }
    return newRes;
}