#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr), diameter(0) {}
    ~BinaryTree() {
        destroyTree(root);
    }

    void destroyTree(TreeNode *node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    TreeNode* buildTreeHelper(int pre[], int preStart, int preEnd,
                              int in[], int inStart, int inEnd) {
        if (preStart > preEnd || inStart > inEnd) {
            return nullptr;
        }

        int rootVal = pre[preStart];
        TreeNode* node = new TreeNode(rootVal);

        // 在中序遍历中找到根节点的位置
        int rootPos = inStart;
        while (rootPos <= inEnd && in[rootPos] != rootVal) {
            rootPos++;
        }

        // 如果没找到，输入无效
        if (rootPos > inEnd) {
            // 输入数据有误，抛出错误或者处理异常
            return nullptr;
        }

        int leftTreeSize = rootPos - inStart;
        node->left = buildTreeHelper(pre, preStart + 1, preStart + leftTreeSize,
                                     in, inStart, rootPos - 1);
        node->right = buildTreeHelper(pre, preStart + leftTreeSize + 1, preEnd,
                                      in, rootPos + 1, inEnd);
        return node;
    }

    void buildTree(int pre[], int in[], int n) {
        root = buildTreeHelper(pre, 0, n - 1, in, 0, n - 1);
    }

    // 计算二叉树的直径
    int diameterOfBinaryTree() {
        diameter = 0;
        depth(root);
        return diameter;
    }

private:
    TreeNode *root;
    int diameter;

    // 计算节点的深度，同时更新直径
    int depth(TreeNode *node) {
        if (node == nullptr) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        // 更新直径：左子树深度 + 右子树深度
        if (leftDepth + rightDepth > diameter) {
            diameter = leftDepth + rightDepth;
        }
        // 返回节点的深度
        return max(leftDepth, rightDepth) + 1;
    }

    // 手动实现 max 函数，避免使用 STL
    int max(int a, int b) {
        return (a > b) ? a : b;
    }
};

int main() {
    int n;
    cin >> n;

    int *pre = new int[n];
    int *in = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> pre[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> in[i];
    }

    BinaryTree tree;
    tree.buildTree(pre, in, n);

    int diameter = tree.diameterOfBinaryTree();
    cout << diameter << endl;

    delete[] pre;
    delete[] in;

    return 0;
}