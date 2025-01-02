#include <functional>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<class T>
struct TreeNode {
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(T v): val(v), left(nullptr), right(nullptr) {}
};

template<class T>
class BST {
    using Node = TreeNode<T>;
    using Compare = function<bool(const T&, const T&)>;
    using TraverseFunc = function<void(const Node*)>;

public:
    BST() : root(nullptr), cmp(less<T>()) {}

    void insert(const T& val) {
        function<Node*(Node*, const T&)> helper = [&helper, this](Node* node, const T& val) -> Node* {
            if (node == nullptr) {
                return new Node(val);
            }
            if (this->cmp(val, node->val)) {
                node->left = helper(node->left, val);
            } else {
                node->right = helper(node->right, val);
            }
            return node;
        };
        root = helper(root, val);
    }

    void remove(const T& val) {
        // 树为空，直接返回
        if (root == nullptr)
            return;
        Node* cur = root, * pre = nullptr;

        // 循环查找
        while (cur != nullptr) {
            if (cur->val == val) {
                break;
            }
            pre = cur;
            if (cmp(cur->val, val)) {
                cur = cur->right;
            } else {
                cur = cur->left;
            }
        }

        if (cur == nullptr)
            return;

        if (cur->left == nullptr || cur->right == nullptr) {
            // 子节点0或1
            Node* child = (cur->left != nullptr) ? cur->left : cur->right;
            if (cur != root) {
                if (pre->left == cur) {
                    pre->left = child;
                } else {
                    pre->right = child;
                }
            } else {
                root = child;
            }
            delete cur;
        } else {
            Node* tmp = cur->left;
            Node* tmpParent = cur;
            while (tmp->right != nullptr) {
                tmpParent = tmp;
                tmp = tmp->right;
            }
            cur->val = tmp->val;
            if (tmpParent->left == tmp) {
                tmpParent->left = tmp->left;
            } else {
                tmpParent->right = tmp->left;
            }
            delete tmp;
        }
    }

    void levelOrder(TraverseFunc func) {
        vector<Node*> seq;
        traverseLOrder(root, seq);
        for (auto v : seq) {
            func(v);
        }
    }

    void printLOrder() {
        levelOrder([](const Node* node) {
            cout << node->val << " ";
        });
    }

private:
    Node* root;
    Compare cmp;

    void traverseLOrder(Node* node, vector<Node*>& seq) {
        if (node == nullptr) return;
        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            seq.push_back(curr);
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    BST<int> bst;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        bst.insert(tmp);
    }
    for (int i = 0; i < m; i++) {
        int tmp;
        cin >> tmp;
        bst.remove(tmp);
    }
    bst.printLOrder();
    return 0;
}