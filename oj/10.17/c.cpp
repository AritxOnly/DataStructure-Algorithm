#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int>bubbles(n);
    for (int i = 0; i < n; i++) {
        cin >> bubbles[i];
    }
    auto it = bubbles.begin();
    while (k != 0 && it != bubbles.end()) {
        if (*it > *(next(it))) {
            bubbles.erase(it);
            k--;
        } else {
            it++;
        }
    }
    while (k != 0) {
        auto max = bubbles.begin();
        for (auto it = bubbles.begin(); it != bubbles.end(); it++) {
            if (*it > *max) {
                max = it;
            }
        }
        bubbles.erase(max);
        k--;
    }
    bool front = true;
    for (int elm : bubbles) {
        if ((elm == 0 && !front) || elm != 0) {
            front = false;
            cout << elm;
        }
    }
    if (bubbles.empty()) {
        cout << 0;
    }
    return 0;
}