#include <iostream>
#include <ostream>
#include <string>

template<class T>
struct ListNode {
    T data;
    ListNode* next;
    ListNode(T x) : data(x), next(nullptr) {}
};

template<class T>
class LinkedList {
public:
    typedef ListNode<T> Node;
    typedef ListNode<T>* NodeRef;

    LinkedList() : head(nullptr), tail(nullptr) {}
    ~LinkedList() { clear(); }

    void push_back(T value) {
        NodeRef node = new Node(value);
        if (head == nullptr) {
            head = node;
            tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }    

    void clear() {
        if (head == nullptr)
            return;
        NodeRef p = head;
        while (p != nullptr) {
            NodeRef del = p;
            p = p->next;
            delete del;
        }
        head = nullptr;
    }

    // 重载+=操作符
    LinkedList& operator+=(const T& other) {
        this->push_back(other);
        return *this;
    }

    // 重载流输出操作符
    std::ostream& operator<<(std::ostream& out) const {
        NodeRef p = head;
        if (head == nullptr) {
            return out;
        }
        while (p != nullptr) {
            out << p->data;
            p = p->next;
        }
        return out;
    }
    
    void print(std::string split = "") {
        if (head == nullptr) {
            return;
        }
        NodeRef p = head;
        while (p != nullptr) {
            std::cout << p->data << split;
            p = p->next;
        }
    }

private:
    NodeRef head = nullptr;
    NodeRef tail = nullptr;
};

template<class T>
// before: std::ostream& operator<<(std::ostream& out, LinkedList<T> list) 
std::ostream& operator<<(std::ostream& out, LinkedList<T>& list) {
    list.operator<<(out);
    return out;
}

using namespace std;

int main() {
    string str;
    cin >> str;
    bool bar = false;
    LinkedList<char> newStr;
    char prevChar = (str.empty()) ? '-' :str[0];
    for (const auto& ch : str) {
        if (ch == '-') {
            bar = true;
            continue;
        }
        if (bar) {
            if (static_cast<int>(prevChar) <= static_cast<int>(ch)) {
                for (char i = prevChar + 1; i < ch; i++) {
                    newStr += i;
                }
            } else {
                for (char i = prevChar - 1; i > ch; i--) {
                    newStr += i;
                }
            }
            bar = false;
        }
        newStr += ch;
        prevChar = ch;
    }
    cout << newStr << endl;
    return 0;
}