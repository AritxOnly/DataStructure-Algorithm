#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    int depth;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v, int d) : val(v), depth(d), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    // 使用前序遍历数组构建二叉树
    TreeNode* build_tree(int arr[], int &index, int size, int depth) {
        if (index >= size || arr[index] == -1) {
            index++;
            return nullptr;
        }
        TreeNode* node = new TreeNode(arr[index++], depth);
        node->left = build_tree(arr, index, size, depth + 1);
        node->right = build_tree(arr, index, size, depth + 1);
        return node;
    }

    void insert_from_array(int arr[], int size) {
        int index = 0;
        sz = size;
        root = build_tree(arr, index, size, 0);
    }

    bool is_odd_even_tree() {
        if (root == nullptr) return false;
        queue<TreeNode *>q;
        vector<TreeNode *>seq;
        q.push(root);
        while (!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            seq.push_back(node);
            if (node->left != nullptr) q.push(node->left);
            if (node->right != nullptr) q.push(node->right);
        }
        int flag = true;
        int depth = seq[0]->depth;
        for (int i = 1; i < seq.size() && flag; i++) {
            int cur_depth = seq[i]->depth;
            if (depth == cur_depth) {
                if (depth % 2 == 0) {
                    if (seq[i]->val % 2 == 0 || seq[i - 1]->val >= seq[i]->val) {
                        flag = false;
                    }
                } else {
                    if (seq[i]->val % 2 == 1 || seq[i - 1]->val <= seq[i]->val) {
                        flag = false;
                    }
                }
            }
            depth = cur_depth;
        }
        return flag;
    }

public:
    TreeNode* root;
    int sz;
};

const int MAXN = 100005;

int main() {
    int n;
    cin >> n;
    int arr[MAXN] = { 0 };
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    BinaryTree tree;
    tree.insert_from_array(arr, n);
    cout << (tree.is_odd_even_tree() ? "true" : "false") << endl;
    return 0;
}