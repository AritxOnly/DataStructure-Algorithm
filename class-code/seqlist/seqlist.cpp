/**
 * A program to implement a sequential list data structure in C++
 */

#include "seqlist.h"
#include <cstddef>
#include <stdexcept>

template<class T>
SeqList<T>::SeqList() {
    arr = new T[capacity];
    size = 0;
}

template<class T>
SeqList<T>::SeqList(const SeqList<T>& other) {
    size = other.size;
    capacity = other.capacity;
    arr = new T[capacity];
    for (size_t i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

template<class T>
SeqList<T>::SeqList(size_t n, T value) {
    while (n > capacity) {
        this->expand();
    }

    for (size_t i = 0; i < n; i++) {
        arr[i] = value;
    }

    size = n;
}

template<class T>
SeqList<T>::~SeqList() {
    delete[] arr;
}

template<class T>
void SeqList<T>::insert(size_t index, const T& value) {
    if (size == capacity) {
        this->expand();
    }

    for (size_t i = size; i > index; i--) {
        // 全部移动
        arr[i] = arr[i - 1];
    }

    arr[index] = value;
}

template<class T>
T& SeqList<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<class T>
void SeqList<T>::qsort() {
    if (size <= 1) {
        return;
    }
    // unfinished
}

template<class T>
void SeqList<T>::expand() {
    T* new_arr = new T[capacity * 2];
    for (size_t i = 0; i < size; i++) {
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    capacity *= 2;
}
