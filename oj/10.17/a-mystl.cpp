#include <iostream>
#include <stack>

using namespace std;

typedef struct Mem_Block {
    int addr;
    int size;
    // bool occupied;
    Mem_Block *next;
    Mem_Block *prev;
    Mem_Block(int _addr, int _size) : 
        addr(_addr), size(_size), next(nullptr), prev(nullptr) {}
} Mem_Block;

class Mem_Pool {
public:
    Mem_Pool() : head(nullptr), tail(nullptr), ptr(nullptr), blocks(0) {}

    void insert(int addr, int size) {
        Mem_Block *block = new Mem_Block(addr, size);
        if (head == nullptr) {
            head = block;
            tail = block;
            block->next = head;
            block->prev = tail;
            blocks++;
        } else {
            tail->next = block;
            block->prev = tail;
            tail = block;
            block->next = head;
            head->prev = block;
            blocks++;
        }
        ptr = head;
    }

    void allocate_block(int s) {
        Mem_Block *cur = ptr;
        if (cur == nullptr) {
            return;
        }
        stack<Mem_Block*>satisfied_blocks;  // 满足条件的块构成的单调栈，取栈底作为最小
        while (true) {
            if (cur->size >= s) {
                int top_size = satisfied_blocks.empty() ?
                               -1 : satisfied_blocks.top()->size;
                while (top_size > cur->size) {
                    satisfied_blocks.pop();
                    top_size = satisfied_blocks.empty() ?
                               -1 : satisfied_blocks.top()->size;
                }
                if (top_size < cur->size)
                    satisfied_blocks.push(cur);
            }
            cur = cur->next;
            if (cur == ptr) {
                break;
            }
        }
        Mem_Block *min = nullptr;
        while (!satisfied_blocks.empty()) {
            min = satisfied_blocks.top();
            satisfied_blocks.pop();
        }
        if (min == nullptr) {
            return;
        } 
        if (min->size == s) {
            ptr = min->next;
            auto cur = min;
            min->prev->next = ptr;
            ptr->prev = min->prev;
            delete cur;
            blocks--;
        } else if (min->size > s) {
            min->size -= s;
        }
    }

    void display_free_space() {
        Mem_Block *cur = ptr;
        while (true) {
            cout << cur->addr << " " << cur->size << endl;
            cur = cur->next;
            if (cur == ptr) {
                break;
            }
        }
    }

private:
    Mem_Block *head;
    Mem_Block *tail;
    Mem_Block *ptr;
    int blocks; // 块数量
};

int main() {
    int n;
    cin >> n;
    Mem_Pool mpool;
    for (int i = 0; i < n; i++) {
        int a, s;
        cin >> a >> s;
        mpool.insert(a, s);
    }
    int tmp;
    while (true) {
        cin >> tmp;
        if (tmp == -1) {
            break;
        }
        mpool.allocate_block(tmp);
    }
    mpool.display_free_space();
    return 0;
}