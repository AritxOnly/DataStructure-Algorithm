#include <iostream>
#include <string>
#include <utility>

using namespace std;

struct TreeNode {
    pair<char, int> val;

    TreeNode *left;
    TreeNode *right;
    TreeNode(pair<char, int> v) : val(std::move(v)), left(nullptr), right(nullptr) {}
};

class HuffmanTree {
public:
    HuffmanTree() : root(nullptr) {}
    HuffmanTree(vector<pair<char, int>>& v) {
        buildTree(v);
    }

    void buildTree(vector<pair<char, int>>& v) {
        int n = v.size();
        vector<TreeNode*> nodes; // 使用数组存储节点，避免STL

        // 创建叶子节点
        for (int i = 0; i < n; ++i) {
            nodes.push_back(new TreeNode(v[i]));
        }

        int node_count = n;
        while (node_count > 1) {
            // 找到两个频率最小的节点
            int min1 = -1, min2 = -1;
            for (int i = 0; i < node_count; ++i) {
                if (min1 == -1 || nodes[i]->val.second < nodes[min1]->val.second) {
                    min2 = min1;
                    min1 = i;
                } else if (min2 == -1 || nodes[i]->val.second < nodes[min2]->val.second) {
                    min2 = i;
                }
            }

            // 合并两个节点
            int combined_freq = nodes[min1]->val.second + nodes[min2]->val.second;
            TreeNode* merged = new TreeNode({'#', combined_freq});
            merged->left = nodes[min1];
            merged->right = nodes[min2];

            // 替换 min1 节点为合并节点，并移除 min2 节点
            nodes[min1] = merged;
            nodes[min2] = nodes[node_count - 1]; // 将最后一个节点移动到 min2 的位置
            node_count--; // 节点数量减一
        }

        // Huffman树的根节点
        root = nodes[0];
    }

    int WPL() {
        return WPLHelper(root, 0);
    }

    int WPLHelper(TreeNode* node, int depth) {
        if (node == nullptr)
            return 0;
        int cur_val = (node->val.first != '#') ? (node->val.second * depth) : 0;
        return cur_val + WPLHelper(node->left, depth + 1) + WPLHelper(node->right, depth + 1);
    }

private:
    TreeNode* root;
};

int main() {
    string str;
    cin >> str;
    vector<pair<char, int>> v;
    auto f = [](vector<pair<char, int>>& v, char key) -> int {
        for (int i = 0; i < v.size(); i++) {
            if (key == v[i].first)
                return i;
        }
        return -1;
    };
    for (auto each : str) {
        int ret = f(v, each);
        if (ret == -1) {
            v.push_back({each, 1});
        } else {
            v[ret].second++;
        }
    }
    HuffmanTree ht(v);
    cout << ht.WPL() << endl;
    return 0;
}