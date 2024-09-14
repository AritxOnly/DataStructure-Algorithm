#include "seqlist.h"
#include <stdexcept>

#define _TPL template<class T>
#define _SL SeqList<T>

_TPL
_SL::SeqList() : capacity(0), size(0), arr(nullptr) {}

_TPL
_SL::~SeqList() { 
    if (arr != nullptr)
        delete[]arr; 
}

_TPL
void _SL::expand() {
    if (capacity == 0) {
        capacity = DEFAULT_CAPACITY;
    }

    if (capacity > MAX_SIZE) {
        throw std::overflow_error("Capacity out of range");
    }

    capacity *= 2;
    T* newArr = new T[capacity];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[]arr;
    arr = newArr;
}