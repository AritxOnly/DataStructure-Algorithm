#include <iostream>
#include <vector>
#include <unordered_map>

/*
 * 思路：通过map存储当前节点的idx，降低搜索时间复杂度到O(logn)
 */

using namespace std;

template<class T>
class BSTPro {
public:
    BSTPro(int n) {
        datas = vector<T>(n * n + n);
    };

    void insert(T v) {
        int idx = 0;
        while (datas[idx] != 0) {
            if (v < datas[idx]) {
                idx = leftChild(idx);
            } else {
                idx = rightChild(idx);
            }
        }
        datas[idx] = v;
        idxs[v] = idx;
    }

    T& getParent(T v) {
        int idx = idxs[v];
        return datas[parent(idx)];
    }

private:
    vector<T> datas;
    unordered_map<T, int> idxs;

    inline int parent(int idx) {
        return (idx - 1) / 2;
    }

    inline int leftChild(int idx) {
        return idx * 2 + 1;
    }

    inline int rightChild(int idx) {
        return idx * 2 + 2;
    }
};

template<class T>
class BSTMax {
    using Node = struct TreeNode {
        T val;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        TreeNode(T v, TreeNode* p) : val(v), left(nullptr), right(nullptr), parent(p) {}
    };

public:
    BSTMax() : root(nullptr) {}

    void insert(T v) {
        if (root == nullptr) {
            root = new Node(v, nullptr);
            mp[v] = root;
            return;
        }
        insertHelper(v, root);
    }

    T& getParent(T v) {
        return mp[v]->parent->val;
    }

private:
    unordered_map<T, Node*> mp;
    Node* root;

    void insertHelper(T v, Node* node) {
        if (node == nullptr) return;

        if (v < node->val) {
            if (node->left == nullptr) {
                node->left = new Node(v, node);
                mp[v] = node->left;
            } else {
                insertHelper(v, node->left);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node(v, node);
                mp[v] = node->right;
            } else {
                insertHelper(v, node->right);
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    BSTMax<long long> bst;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        bst.insert(v[i]);
    }
    for (int i = 1; i < n; i++) {
        cout << bst.getParent(v[i]) << " ";
    }
    return 0;
}