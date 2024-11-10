#include <iostream>

using namespace std;

struct TreeNode {
    short ltag, rtag;
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char v) : ltag(0), rtag(0), val(v), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    BinaryTree() : root(nullptr) {}

    TreeNode* buildTreeHelper(string& arr, int& index, int size) {
        if (index >= size || arr[index] == '0') {
            index++;
            return nullptr;
        }
        TreeNode* node = new TreeNode(arr[index++]);
        node->left = buildTreeHelper(arr, index, size);
        node->right = buildTreeHelper(arr, index, size);
        return node;
    }

    void buildTreeFromArray(string& arr, int size) {
        int index = 0;
        root = buildTreeHelper(arr, index, size);
    }

    void createInThread() {
        TreeNode* pre = nullptr;
        if (root != nullptr) {
            createInThread(root, pre);
            if (pre != nullptr) {
                pre->right = nullptr;
                pre->rtag = 1;
            }
        }
    }

    void printInOrderThread() const {
        TreeNode* current = root;
        if (current != nullptr) {
            // 移动到最左下的节点
            while (current->ltag == 0) {
                current = current->left;
            }
            // 开始按照线索遍历
            while (current != nullptr) {
                // 输出节点信息
                cout << current->ltag << " ";
                if (current->left != nullptr) {
                    cout << current->left->val;
                } else {
                    cout << 0;
                }
                cout << " " << current->val << " ";
                if (current->right != nullptr) {
                    cout << current->right->val;
                } else {
                    cout << 0;
                }
                cout << " " << current->rtag << endl;

                // 按照线索移动到下一个节点
                if (current->rtag == 1) {
                    current = current->right;
                } else {
                    current = current->right;
                    while (current != nullptr && current->ltag == 0) {
                        current = current->left;
                    }
                }
            }
        }
    }

private:
    TreeNode* root;

    void createInThread(TreeNode* current, TreeNode*& pre) {
        if (current == nullptr) {
            return;
        }
        createInThread(current->left, pre);
        if (current->left == nullptr) {
            current->left = pre;
            current->ltag = 1;
        }
        if (pre != nullptr && pre->right == nullptr) {
            pre->right = current;
            pre->rtag = 1;
        }
        pre = current;
        createInThread(current->right, pre);
    }
};

int main() {
    BinaryTree tree;
    string str;
    cin >> str;
    tree.buildTreeFromArray(str, str.length());
    tree.createInThread();
    tree.printInOrderThread();
    return 0;
}