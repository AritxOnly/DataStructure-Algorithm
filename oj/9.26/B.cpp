#include <iostream>

using namespace std;

typedef struct Node {
    int no;
    Node* next;
    Node(int no) : no(no), next(nullptr) {}
} Node;
typedef Node* NodePtr;

NodePtr head = nullptr;
int size_ = 0;
const int MAX_SIZE = 1000005;

bool in(int num) {
    NodePtr cur = head;
    while (cur != nullptr) {
        if (cur->no == num)
            return true;
    }
    return false;
}

void insert(int num) {
    if (size_ >= MAX_SIZE && in(num))
        return;
    size_++;
    if (head == nullptr) {
        NodePtr node = new Node(num);
        head = node;
        return;
    }
    NodePtr cur = head;
    NodePtr pre = cur;
    while (cur != nullptr) {
        if (cur->no > num && pre->no < num) {
            // 将num插入这两个中间
            NodePtr node = new Node(num);
            pre->next = node;
            node->next = cur;
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    NodePtr node = new Node(num);
    pre->next = node;
}

int at(int index) {
    int i = 0;
    NodePtr cur = head;
    while (cur != nullptr) {
        if (i == index) return cur->no;
        i++;
        cur = cur->next;
    }
    return -1;  // 越界
}

void generate(int base) {
    insert(base);
    NodePtr cur = head;
    while (cur != nullptr) {
        insert(cur->no * 2 + 1);
        insert(cur->no * 3 + 1);
    }
}

int main() {
    int base;
    cin >> base;
    generate(base);
    int n;
    cin >> n;
    cout << at(n);
    return 0;
}