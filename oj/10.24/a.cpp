#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    // 使用前序遍历数组构建二叉树
    TreeNode* build_tree(int arr[], int &index, int size) {
        if (index >= size || arr[index] == -1) {
            index++;
            return nullptr;
        }
        TreeNode* node = new TreeNode(arr[index++]);
        node->left = build_tree(arr, index, size);
        node->right = build_tree(arr, index, size);
        return node;
    }

    void insert_from_array(int arr[], int size) {
        int index = 0;
        root = build_tree(arr, index, size);
    }

    // 合并两棵树
    static TreeNode* merge_trees(TreeNode* t1, TreeNode* t2) {
        if (!t1) return t2;
        if (!t2) return t1;
        TreeNode* merged = new TreeNode(t1->val + t2->val);
        merged->left = merge_trees(t1->left, t2->left);
        merged->right = merge_trees(t1->right, t2->right);
        return merged;
    }

    // 前序遍历打印树
    void pre_order_print(TreeNode* node) {
        if (!node) {
            cout << -1 << " ";
            return;
        }
        cout << node->val << " ";
        pre_order_print(node->left);
        pre_order_print(node->right);
    }

    void print() {
        pre_order_print(root);
        cout << endl;
    }
};

int main() {
    int a, b;
    cin >> a >> b;
    int* a_arr = new int[a];
    int* b_arr = new int[b];
    for (int i = 0; i < a; ++i) {
        cin >> a_arr[i];
    }
    for (int j = 0; j < b; ++j) {
        cin >> b_arr[j];
    }

    BinaryTree tree1, tree2, merged_tree;
    tree1.insert_from_array(a_arr, a);
    tree2.insert_from_array(b_arr, b);

    merged_tree.root = BinaryTree::merge_trees(tree1.root, tree2.root);

    merged_tree.print();

    delete[] a_arr;
    delete[] b_arr;

    return 0;
}