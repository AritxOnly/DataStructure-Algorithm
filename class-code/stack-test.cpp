#include <cstddef>
#include <cstdio>

template <class T>
class Stack {
public:
    Stack() {
        data = new T[m_capacity];
        m_size = 0;
        m_top = -1;
    }

    Stack(size_t size, T value) {
        int cell = size / m_capacity + 1;
        m_capacity *= cell;
        data = new T[m_capacity];
        for (int i = 0; i < size; i++) {
            data[i] = value;
        }
        m_size = size;
        m_top = size - 1;
    }

    ~Stack() {
        delete[]data;
    }

    void push(T value) {
        if (m_size == m_capacity) {
            // 扩容
            T *new_data = new T[m_capacity * 2];
            for (int i = 0; i < m_size; i++) {
                new_data[i] = data[i];
            }
            delete[]data;
            data = new_data;
            m_capacity *= 2;
        }
        data[++m_top] = value;
        m_size++;
    }

    void pop() {
        if (m_size == 0) {
            throw "Stack is empty";
        }
        m_size--;
        m_top--;
    }

    T top() {
        if (m_size == 0) {
            throw "Stack is empty";
        }
        return data[m_top];
    }

    size_t size() {
        return m_size;
    }

private:
    T *data;
    size_t m_top;
    size_t m_size;
    size_t m_capacity = 100;
};

int main() {
    Stack<int>s(6, 10);
    s.push(1);
    s.push(2);
    s.push(3);
    printf("%d\n", s.top());
    s.pop();
    printf("%d\n", s.top());
    s.pop();
    return 0;
}