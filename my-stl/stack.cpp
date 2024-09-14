#include "stack.h"
#include "abstract-data-structure/seqlist.h"
#include <cassert>
#include <ostream>
#include <stdexcept>
#include <utility>

using namespace MyStl;

template<class T>
stack<T>::stack() : SeqList<T>(), top(-1) {
    assert(capacity == 0);  // 断言
}

template<class T>
stack<T>::stack(int _size) : SeqList<T>(), top(_size - 1) {
    if (_size <= 0)
        return;
    capacity = DEFAULT_CAPACITY;
    size = _size;
    while (capacity < _size) {
        capacity *= 2;  // 节省时间的做法，维护性可能略差
    }
    arr = new T[capacity];
}

template<class T>
stack<T>::stack(const int _size, const T& _value) : 
        SeqList<T>(), top(_size - 1) {
    if (_size <= 0)
        return;
    capacity = DEFAULT_CAPACITY;
    size = _size;
    while (capacity < _size) {
        capacity *= 2;  // 节省时间的做法，维护性可能略差
    }
    arr = new T[capacity];
    for (int i = 0; i < _size; i++) {
        arr[i] = _value;
    }
}

template<class T>
stack<T>::stack(const stack<T>& other) {
    // 深拷贝
    capacity = other.capacity;
    size = other.size;
    top = other.top;
    arr = new T[capacity];
    for (int i = 0; i <= top; i++) {
        arr[i] = other.arr[i];
    }
}

template<class T>
const T& stack<T>::getTop() const {
    return arr[top];
}

template<class T>
bool stack<T>::pop() {
    if (size == 0) {
        return false;
    }
    top--;
    size--;
    return true;
}

template<class T>
void stack<T>::push(const T& _value) {
    if (size == capacity)
        this->expand();
    arr[++top] = _value;
    size++;
}

template<class T>
void stack<T>::swap(stack<T>& other) {
    std::swap(arr, other.arr);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
    std::swap(top, other.top);
}

template<class T>
stack<T>& stack<T>::operator=(const stack<T>& other) {
    // 深拷贝
    if (arr != nullptr)
        delete[]arr;
    capacity = other.capacity;
    size = other.size;
    top = other.top;
    arr = new T[capacity];
    for (int i = 0; i <= top; i++) {
        arr[i] = other.arr[i];
    }
    return *this;
}

template<class T>
T& stack<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Stack index out of range");
    }
    return arr[index];
}

template<class T>
std::ostream& stack<T>::operator<<(std::ostream& out) {
    out << "stack bottom ->";
    for (int i = 0; i < size; i++) {
        out << " | " << arr[i];
    }
    out << " -> stack top\n";
    return out;
}

template<class T>
stack<T> stack<T>::operator+(const stack<T>& other) const {
    stack<T> ret(size + other.size);
    for (int i = 0; i < size; i++) {
        ret[i] = arr[i];
    }
    for (int i = 0; i < other.size; i++) {
        ret[i + size] = other.arr[i];
    }
    return ret;
}

template<class T>
stack<T> stack<T>::operator*(const int times) const {
    if (times < 1)
        return stack<T>();  // 返回空对象
    stack<T> ret(size * times);
    for (int iteration = 0; iteration < times; iteration++) {
        for (int i = 0; i < size; i++) {
            ret[size * iteration + i] = arr[i];
        }
    }
    return ret;
}

template<class T>
stack<T>& stack<T>::operator+=(const stack<T>& other) {
    int _size = size + other.size;
    while (_size > capacity) {
        this->expand();
    }
    for (int i = size; i < _size; i++) {
        arr[i] = other.arr[i - size];
    }
    size = _size;
    top = _size - 1;
    return *this;
} 

template<class T>
stack<T>& stack<T>::operator*=(const int times) {
    int _size = size * times;
    while (_size > capacity) {
        this->expand();
    }
    for (int iteration = 1; iteration < times; iteration++) {
        for (int i = 0; i < size; i++) {
            arr[iteration * size + i] = arr[i];
        }
    }
    size = _size;
    top = _size - 1;
    return *this;
}