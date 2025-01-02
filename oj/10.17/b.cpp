#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <deque>

using namespace std;

const int MAXN = 10005;

int nseq[MAXN], sseq[MAXN];

int ExistingPeople(vector<deque<pair<int, int>>>& seq) {
    int num = 0;
    for (auto q : seq) {
        num += q.size();
    }
    return num;
}

deque<pair<int, int>>::iterator NormalExist(deque<pair<int, int>>& window) {
    for (auto it = window.begin(); it != window.end(); it++) {
        if (it->second == 0) {
            return it;
        }
    }
    return window.end();
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    using Window = deque<pair<int, int>>;  // deque用于模拟队列，
                // pair的first表示入队时间，second用1代表特殊用户，0代表普通用户
    vector<Window>normal(a);    // 对私窗口
    vector<Window>special(b);   // 特殊窗口

    int noc = 0, soc = 0;   // 被占用的对私窗口和特殊窗口数
    for (int i = 0; i < n; i++) {
        cin >> nseq[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> sseq[i];
    }

    for (int t = 0; t < n; t++) {
        int people = ExistingPeople(normal) + nseq[t];  // 目前办理普通业务的人数
        int avr = people / a;
        int rm = people % a;
        if (avr + ((rm == 0) ? 0 : 1) > 7) {
            // 开启特殊窗口的逻辑
            
        } else {
            for (auto window : normal) {
                int cur = window.size();
                int r = avr - cur;
                for (int k = 0; k < r; k++) {
                    window.push_back(pair<int, int>(t, 0));
                }
                auto customer = window.front();
                cout << t - customer.first << " ";
                window.pop_front();
            }
            for (int k = 0; k < rm; k++) {
                normal[k].push_back(pair<int, int>(t, 0));
            }
            int sp = ExistingPeople(special) + sseq[t];
            int savr = sp / a;
            int srm = sp % a;
            for (auto window : special) {
                auto np = NormalExist(window);
                int r = savr - window.size();
                if (np == window.end()) {
                    for (int i = 0; i < r; i++) {
                        window.push_back(pair<int, int>(t, 1));
                    }
                } else {
                    for (int i = 0; i < r; i++) {
                        window.insert(prev(np), pair<int, int>(t, 1));
                    }
                }
            }
        }
    }

    return 0;
}