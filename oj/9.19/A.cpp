#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(T data, Node* next = nullptr, Node* prev = nullptr) :
        data(data), next(next), prev(prev) {}
};

template<class T>
class Deque {
public:
    typedef Node<T>* NodePtr;

    Deque() {}

    Deque(int size, T* arr) {
        for (int i = 0; i < size; i++) {
            this->push_back(arr[i]);
        }
    }

    void push_front(const T& value) {
        NodePtr node = new Node<T>(value);
        if (head == nullptr) {
            head = node;
            tail = node;
            ++size;
            return;
        }
        node->next = head;
        head->prev = node;
        head = node;
        ++size;
    }

    T pop_front() {
        if (size <= 0)
            throw out_of_range("empty deque");
        T _value = head->data;
        NodePtr cur = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        delete cur;
        --size;
        if (size == 0) {
            head = nullptr;
            tail = nullptr;
        }
        return _value;
    }

    void push_back(const T& value) {
        NodePtr node = new Node<T>(value);
        if (head == nullptr) {
            head = node;
            tail = node;
            ++size;
            return;
        }
        if (tail != nullptr) {
            tail->next = node;
            node->prev = tail;
            tail = tail->next;
            ++size;
        }
    }

    T pop_back() {
        if (size <= 0)
            throw out_of_range("empty deque");
        T _value = tail->data;
        NodePtr cur = tail;
        tail = tail->prev;
        if (tail != nullptr)
            tail->next = nullptr;
        delete cur;
        --size;
        if (size == 0) {
            tail = nullptr;
            head = nullptr;
        }
        return _value;
    }

    bool empty() {
        return (size == 0) ? true : false;
    }

    void print() {
        NodePtr p = head;
        while (p != nullptr) {
            cout << p->data << " ";
            p = p->next;
        }
    }

private:
    NodePtr head = nullptr;
    NodePtr tail = nullptr;
    int size = 0;
};

int main() {
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Deque<int> cards(n, arr);   // 初始化卡片
    Deque<int> res;
    // 逆向操作还原
    while (!cards.empty()) {
        int show = cards.pop_back();    // 取得刚刚展示的牌
        if (res.empty()) {
            res.push_back(show);
            continue;
        }
        int bottom = res.pop_back();    // 取得刚刚被放到牌堆底下的牌
        // 将展示的牌和放到底下的牌按顺序放到牌堆顶上
        res.push_front(bottom);
        res.push_front(show);
    }

    res.print();
    return 0;
}