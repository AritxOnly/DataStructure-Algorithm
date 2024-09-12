#include <iostream>

struct Node {
    int id;
    Node* prev;
    Node* next;
    Node(int x, Node* prev = nullptr, Node* next = nullptr) : 
        id(x), prev(prev), next(next) {}
};

typedef Node* NodeRef;

class DlList {
public:
    DlList(int n) {
        for (int i = 1; i <= n; i++)
            insert(i);
    }

    ~DlList() { clear(); }

    void insert(int id) {
        NodeRef node = new Node(id);
        if (first == nullptr) {
            node->next = node;
            node->prev = node;
            first = node;
            return;
        }
        NodeRef last = first->prev;
        node->next = last->next;
        node->prev = last;
        last->next = node;
        node->next->prev = node;
    }

    bool remove(NodeRef pos) {
        if (pos == pos->next && pos == pos->prev)   {
            // 只剩一个元素了
            std::cout << pos->id << " ";
            delete pos;
            first = nullptr;
            return false;
        }
        NodeRef prev = pos->prev;
        NodeRef next = pos->next;
        prev->next = next;
        next->prev = prev;
        std::cout << pos->id << " ";
        delete pos;
        return true;
    }

    void clear() {
        if (first == nullptr) 
            return;
        NodeRef p = first->next;
        while (p != first) {
            NodeRef del = p;
            p = p->next;
            delete del;
        }
        delete first;
        first = nullptr;
    }

    NodeRef getFirst() {
        return first;
    }

private:
    NodeRef first = nullptr;
};

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    DlList dl(n);
    NodeRef p = dl.getFirst();
    bool notRemainOne = true;
    bool reverse = false;
    while (notRemainOne) {
        for (int i = 1; i < m; i++) {
            if (!reverse) {
                p = p->next;
            } else {
                p = p->prev;
            }
        }
        // 此时p停在要被删除的元素上
        NodeRef del = p;
        if (del->id % k == 0) {
            reverse = !reverse;
        }
        if (!reverse) {
            p = p->next;
        } else {
            p = p->prev;
        }
        notRemainOne = dl.remove(del);
        if (!notRemainOne && dl.getFirst() != nullptr) {
            cout << p->id << endl;
        }
    }
    return 0;
}
