template<class T>
class BinarySearchTree {
public:
    typedef struct TreeNode {
        T value;
        TreeNode* left;
        TreeNode* right;
        TreeNode(T& _value, TreeNode* _left, TreeNode* _right) :
            value(_value), left(_left), right(_right) {}
    } Node;
    typedef Node* NodePtr;
    typedef Node& NodeRef;

    BinarySearchTree() : root(nullptr) {}
    NodePtr search(const T& _value) {
        NodePtr cur = root;
        while (cur != nullptr) {
            if (cur->value > _value) {
                cur = cur->left;
            } else if (cur->value < _value) {
                cur = cur->right;
            } else {
                break;
            }
        }
        return cur;
    }

    bool insert(const T& _value) {
        NodePtr cur = root;
        NodePtr prev = cur;
        while (cur != nullptr) {
            prev = cur;
            if (cur->value < _value) {
                cur = cur->right;
            } else if (cur->value > _value) {
                cur = cur->left;
            } else {
                return false;
            }
        }
        if (prev == nullptr) {
            return false;
        }
        if (_value > prev->value) {
            prev->right = new Node(_value);
        } else {
            prev->left = new Node(_value);
        }
        return true;
    }

private:
    NodePtr root;
};