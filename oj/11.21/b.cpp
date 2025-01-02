#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<class T>
class BinaryTree {
public:
    struct TreeNode { 
        T val;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
        bool lightened;
        TreeNode(T v, TreeNode* p = nullptr) 
            : val(v), left(nullptr), right(nullptr), parent(p),
              lightened(false) {}
    };

    BinaryTree() : root(nullptr) {}

    void buildFromLOrder(const vector<T>& arr) {
        int size = arr.size();
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
                if (arr[index] != 0) {
                    current->left = new TreeNode(arr[index], current);
                    q.push(current->left);
                }
                index++;
            }

            // 构建右子节点
            if (index < size) {
                if (arr[index] != 0) {
                    current->right = new TreeNode(arr[index], current);
                    q.push(current->right);
                }
                index++;
            }
        }
    }

    int findMinimumNum() {
        return findMinimumNumHelper(root);
    }

private:
    TreeNode* root;

    int findMinimumNumHelper(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        int min = 1000000;
        if (node->lightened) {
            min = findMinimumNumHelper(node->left) + findMinimumNumHelper(node->right);
        } else {
            if (node->parent == nullptr) {
                // light the lamp
                node->lightened = true;
                if (node->left) node->left->lightened = true;
                if (node->right) node->right->lightened = true;
                min = 1 + findMinimumNumHelper(node->left) + findMinimumNumHelper(node->right);
                // put it back
                node->lightened = false;
                if (node->left) node->left->lightened = false;
                if (node->right) node->right->lightened = false;
                if (!(node->left == nullptr && node->right == nullptr)) {
                    min = std::min(min, findMinimumNumHelper(node->left) + findMinimumNumHelper(node->right));
                }
            } else if (!node->parent->lightened) {
                // light the lamp
                node->lightened = true;
                node->parent->lightened = true;
                if (node->left) node->left->lightened = true;
                if (node->right) node->right->lightened = true;
                min = 1 + findMinimumNumHelper(node->left) + findMinimumNumHelper(node->right);
                // put it back
                node->lightened = false;
                node->parent->lightened = false;
                if (node->left) node->left->lightened = false;
                if (node->right) node->right->lightened = false;
            } else {
                // light the lamp
                node->lightened = true;
                if (node->left) node->left->lightened = true;
                if (node->right) node->right->lightened = true;
                min = 1 + findMinimumNumHelper(node->left) + findMinimumNumHelper(node->right);
                // put it back
                node->lightened = false;
                if (node->left) node->left->lightened = false;
                if (node->right) node->right->lightened = false;
                if (!(node->left == nullptr && node->right == nullptr)) {
                    min = std::min(min, findMinimumNumHelper(node->left) + findMinimumNumHelper(node->right));
                }
            }
        }
        return min;
    }
};

int main() {
    int n;
    cin >> n;
    vector<unsigned char>barn(n);
    for (int i = 0; i < n; i++) {
        cin >> barn[i];
    }
    
    BinaryTree<unsigned char> bt;
    bt.buildFromLOrder(barn);

    cout << bt.findMinimumNum();
    return 0;
}