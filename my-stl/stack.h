#ifndef __STACK_H__
#define __STACK_H__

#include "abstract-data-structure/seqlist.h"
#include <ostream>

template<class T>
class SeqList;

namespace MyStl {
    // 顺序栈
    template<class T>
    class stack : public SeqList<T> {
    public:
        // 构造与析构
        stack();
        stack(const int _size);
        stack(const int _size, const T& _value);
        stack(const stack<T>& other);
        ~stack() = default;

        const T& getTop() const;
        bool pop();
        void push(const T& _value);
        void swap(stack& other);

        // 运算符重载
        stack& operator=(const stack& other);
        T& operator[](int index);
        std::ostream& operator<<(std::ostream& out);
        stack operator+(const stack& other) const;    // 用于合成两个stack
        stack operator*(const int times) const;   // 用于将stack loop拓展times份
        stack& operator+=(const stack& other);
        stack& operator*=(const int time);

        // 引用seqlist抽象对象的成员变量
        using SeqList<T>::arr;
        using SeqList<T>::size;
        using SeqList<T>::capacity;
    
    private:
        int top;
    };
}

template<class T>
std::ostream& operator<<(std::ostream& out, MyStl::stack<T>& stack) {
    stack.operator<<(out);
    return out;
}

#endif