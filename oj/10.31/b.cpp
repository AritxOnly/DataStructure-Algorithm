#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    void buildTreeFromArray(int arr[], int size) {
        if (size == 0 || arr[0] == -1) {
            root = nullptr;
            return;
        }
        root = new TreeNode(arr[0]);
        queue<TreeNode*> q;
        q.push(root);
        int index = 1;
        while (!q.empty() && index < size) {
            TreeNode* current = q.front();
            q.pop();

            // 构建左子节点
            if (index < size) {
                if (arr[index] != -1) {
                    current->left = new TreeNode(arr[index]);
                    q.push(current->left);
                }
                index++;
            }

            // 构建右子节点
            if (index < size) {
                if (arr[index] != -1) {
                    current->right = new TreeNode(arr[index]);
                    q.push(current->right);
                }
                index++;
            }
        }
    }

    int maximumValue() {
        auto result = dfs(root);
        return max(result.first, result.second);
    }

private:
    TreeNode* root;

    // 返回值：pair<不包含当前节点的最大值，包含当前节点的最大值>
    pair<int, int> dfs(TreeNode* node) {
        if (node == nullptr) {
            return {0, 0};
        }
        auto left = dfs(node->left);
        auto right = dfs(node->right);

        // 包含当前节点：当前节点的值 + 不包含左子节点的最大值 + 不包含右子节点的最大值
        int includeCurrent = node->val + left.first + right.first;

        // 不包含当前节点：左右子节点的最大值之和（可以选择包含或不包含它们）
        int excludeCurrent = max(left.first, left.second) + max(right.first, right.second);

        return {excludeCurrent, includeCurrent};
    }
};

int main() {
    BinaryTree tree;
    int n;
    cin >> n;
    if (n <= 0) {
        cout << 0 << endl;
        return 0;
    }
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    tree.buildTreeFromArray(arr, n);
    cout << tree.maximumValue() << endl;
    delete[] arr;
    return 0;
}