#include <iostream>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

class BinaryTree {
    using Func = function<void(int, vector<int>&)>;

public:
    BinaryTree(vector<int>& traverse, int cnt) : nodes(traverse), count(cnt) {}
    ~BinaryTree() = default;

    bool empty() {
        return count == 0;
    }

    void takeOff(int node, Func func) {
        if (empty() || nodes[node] == 0) return;
        if (   (leftChild(node) >= nodes.size() || !nodes[leftChild(node)])
            && (rightChild(node) >= nodes.size() || !nodes[rightChild(node)])   ) {
            func(node, nodes);
            nodes[node] = 0;   // 摘除
            return;
        }
        takeOff(leftChild(node), func);
        takeOff(rightChild(node), func);
    }

    // 优化后的摘除叶子节点函数
    void takeOffPro(Func func, queue<int>& leaves) {
        int n = leaves.size();
        for (int i = 0; i < n; i++) {
            int node = leaves.front();
            leaves.pop();   // 出队
            if (nodes[node] != 0) { // 只有之前非零才需要处理
                func(node, nodes);
                nodes[node] = 0;    // 摘除
                count--;            // 更新计数器
            }
            if (node != 0) {
                int p = parent(node);
                if (p >= 0 && p < nodes.size()) {
                    // 检查父节点是否成为新的叶子
                    bool left_zero = leftChild(p) >= nodes.size() || nodes[leftChild(p)] == 0;
                    bool right_zero = rightChild(p) >= nodes.size() || nodes[rightChild(p)] == 0;
                    if (left_zero && right_zero && nodes[p] != 0) {
                        leaves.push(p);
                    }
                }
            }
        }
    }

    void getLeaves(queue<int>& leaves) {
        stack<int> s;
        s.push(0); // 根节点索引

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (node >= nodes.size() || nodes[node] == 0) continue;

            int l = leftChild(node);
            int r = rightChild(node);
            bool is_leaf = (l >= nodes.size() || nodes[l] == 0) &&
                           (r >= nodes.size() || nodes[r] == 0);
            if (is_leaf) {
                leaves.push(node);
            } else {
                // 为了确保左子节点先被处理，先压入右子节点，再压入左子节点
                if (r < nodes.size() && nodes[r] != 0) {
                    s.push(r);
                }
                if (l < nodes.size() && nodes[l] != 0) {
                    s.push(l);
                }
            }
        }
    }

    void solution(Func func) {
        queue<int> leaves;
        getLeaves(leaves);
        while (!empty()) {
            takeOffPro(func, leaves);
        }
    }

private:
    vector<int> nodes;
    int count;

    /* 数组索引 */
    static inline int parent(int idx) { return (idx - 1) / 2; }
    static inline int leftChild(int idx) { return idx * 2 + 1; }
    static inline int rightChild(int idx) { return idx * 2 + 2; }
};

void print(int idx, vector<int>& nodes) {
    printf("%d ", nodes[idx]);
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (arr[i] != 0) {
            cnt++;
        }
    }
    BinaryTree tree(arr, cnt);
    tree.solution(print);
    return 0;
}