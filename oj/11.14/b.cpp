#include <cstdio>
#include <iostream>

using namespace std;

class HashTable {
public:
    const int EMPTY = 0;

    HashTable(int prime, int sz, int m) : prime(prime), size(sz), m(m) {
        table.resize(size, EMPTY);
    }

    ~HashTable() { table.clear(); };

    bool insert(int num) {
        int idx = hashFunc(num);
        while (table[idx] != EMPTY) {
            idx = (idx + 1) % size;
            if (idx == hashFunc(num)) {
                // 表已满
                return false;
            }
        }
        table[idx] = num;
        return true;
    }

    double ASLSuccess() {
        int total = 0;
        int filledCount = 0;
        for (auto each : table) {
            if (each != EMPTY) {
                bool succ;
                total += count(each, succ);
                filledCount++;
            }
        }
        return static_cast<double>(total) / static_cast<double>(filledCount);
    }

    double ASLUnsucc() {
        int total = 0;
        int searchCount = 0;
        for (int i = 0; i < prime; ++i) {
            int cnt = 1;
            int idx = i;
            while (table[idx] != EMPTY) {
                idx = (idx + 1) % size;
                cnt++;
                if (idx == i) {
                    // 已经回到了起始位置，表已满
                    break;
                }
            }
            total += cnt;
            searchCount++;
        }
        return static_cast<double>(total) / static_cast<double>(searchCount);
    }

private:
    int prime;  // 取模
    int m;      // 表项个数
    int size;   // 表大小
    vector<int> table;

    // 哈希映射
    int hashFunc(int num) {
        return num % prime;
    }

    // 计算成功搜索长度
    int count(int num, bool& succ) {
        int idx = hashFunc(num);
        int cnt = 1;
        int startIdx = idx;
        while (table[idx] != EMPTY) {
            if (table[idx] == num) {
                succ = true;
                return cnt;
            }
            idx = (idx + 1) % size;
            cnt++;
            if (idx == startIdx) {
                succ = false;
                return cnt;
            }
            if (cnt > size) {
                break;
            }
        }
        // 理论上不应到达这里
        succ = false;
        return cnt;
    }
};

int main() {
    int n, prime, m;
    cin >> n >> prime >> m;
    HashTable ht(prime, n, m);
    for (int i = 0; i < m; i++) {
        int tmp;
        cin >> tmp;
        ht.insert(tmp);
    }
    printf("%.3f %.3f", ht.ASLSuccess(), ht.ASLUnsucc());
    return 0;
}