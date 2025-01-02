#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

template<class T>
struct TreeNode {
    using Node = TreeNode<T>;
    T val;
    Node* left;
    Node* right;
    TreeNode(T val) : val(val), left(nullptr), right(nullptr) {}
};

template<class T>
class BinaryTree {
public:
    using Node = TreeNode<T>;

    const int EMPTY = 1000000;

    BinaryTree() : root(nullptr) {}

    void buildTree(vector<T>& arr) {
        queue<Node*> q;

        if (arr.size() == 0 || arr[0] == EMPTY) {
            return;
        }

        Node* node = new Node(arr[0]);
        root = node;
        levelOrder.push_back({0, node});
        q.push(node);

        int idx = 1;
        while (!q.empty() && idx < arr.size()) {
            Node* curr = q.front();
            q.pop();

            if (idx < arr.size() && arr[idx] != EMPTY) {
                curr->left = new Node(arr[idx]);
                q.push(curr->left);
                levelOrder.push_back({idx, curr->left});
            }
            idx++;

            if (idx < arr.size() && arr[idx] != EMPTY) {
                curr->right = new Node(arr[idx]);
                q.push(curr->right);
                levelOrder.push_back({idx, curr->right});
            }
            idx++;
        }
    }

    int findExactSum(int sum) {
        vector<int> path;
        return findExactSumHelper(root, sum, path);
    }

private:
    Node* root;
    vector<pair<int, Node*>> levelOrder;

    int findExactSumHelper(Node* node, int sum, vector<int>& path) {
        if (node == nullptr) {
            return 0;
        }

        int cnt = 0;
        path.push_back(node->val);

        int currSum = 0;
        // 逆序遍历路径，计算从任意节点到当前节点的路径和
        for (int i = path.size() - 1; i >= 0; i--) {
            currSum += path[i];
            if (currSum == sum) {
                cnt++;
            }
        }

        // 递归左子树和右子树
        cnt += findExactSumHelper(node->left, sum, path);
        cnt += findExactSumHelper(node->right, sum, path);

        // 回溯，移除当前节点
        path.pop_back();

        return cnt;
    }
};

int main() {
    int bloodSum, n;
    cin >> bloodSum >> n;

    vector<int>v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    BinaryTree<int>tree;
    tree.buildTree(v);

    cout << tree.findExactSum(bloodSum) << endl;

    return 0;
}