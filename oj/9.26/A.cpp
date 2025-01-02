#include <iostream>
#include <stdexcept>
#include <utility>
#include <ostream>

const long long MAX_SIZE = 2147483647;
const int DEFAULT_CAPACITY = 100;

template<class T>
class SeqList {
public:
    SeqList();
    virtual ~SeqList();

    void clear() {
        if (arr != nullptr)
            delete[]arr;
        size = 0;
        capacity = 0;
        arr = nullptr;
    }

    // 迭代器类定义
    class iterator {
    public:
        iterator(int _index, int _size = 0, T* _arr = nullptr) : 
            index(_index), size(_size), arr(_arr) {
            if (index >= size || index < 0)
                index = -1;
        }

        T& operator*() const {
            if (index >= size) {
                throw std::out_of_range("Index out of range");
            }
            if (arr == nullptr) {
                throw std::overflow_error("arr not initialized");
            }
            return arr[index];
        }

        iterator operator+(const int n) {
            return iterator(index + n, size, arr);
        }

        iterator operator-(const int n) {
            return iterator(index - n, size, arr);
        }

        iterator& operator++() {
            index++;
            if (index >= size) {
                index = -1;
            }
            return *this;
        }

        bool operator!=(const iterator& other) {
            return (index != other.index) ? true : false;
        }

        bool operator==(const iterator& other) {
            return (index == other.index) ? true : false;
        }

        int getIndex() {
            return index;
        }

    private:
        int index = 0;
        int size = 0;
        T* arr = nullptr;
    };

protected:
    T* arr;
    int size;
    int capacity;

    void expand();  // 扩容
};


#define _TPL template<class T>
#define _SL SeqList<T>

_TPL
_SL::SeqList() : arr(nullptr), size(0), capacity(0) {}

_TPL
_SL::~SeqList() {
    if (arr == nullptr) 
        clear();
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
    capacity = (capacity > MAX_SIZE) ? (MAX_SIZE - 1) : capacity;
    T* newArr = new T[capacity];
    for (int i = 0; i < size; i++) {
        newArr[i] = arr[i];
    }
    delete[]arr;
    arr = newArr;
}

namespace MyStl {
    template<class T>
    class vector : public SeqList<T> {
    public:
        // 构造与析构函数
        vector();
        vector(const int _size);
        vector(const int _size, const T& _value);
        vector(const vector& other);
        template<class Iterator>
            vector(const Iterator& _begin, const Iterator& _end);
        ~vector() = default;

        void push_back(const T& _value);
        void pop_back();
        bool empty();
        void reserve(const int _size);
        void swap(vector& other);

        const T& at(const int _index) const;
        const T& front() const;
        const T& back() const;
        T* data();
        const int get_size() const;
        const int get_capacity() const;
        void shrink_to_fit();

        // 运算符重载
        T& operator[](const int index);
        vector& operator=(const vector& other);
        bool operator==(const vector& other);
        bool operator!=(const vector& other);

        /** 
         * ABSTRACT SEQLIST ITERATOR
         * INCLUDE FUNCTION OF DEREFERENCE, ++, != AND ==
         */
        using typename SeqList<T>::iterator;

        // iterator begin();
        // iterator end();
        // iterator iter_at(int _index);

        // void insert(iterator pos, const T& _value);
        // void insert(iterator pos, int n, const T&value);
        // void erase(iterator _start, iterator _end);
        // void erase(iterator pos, int len = 1);

        // 引用seqlist抽象对象的成员变量
        using SeqList<T>::arr;
        using SeqList<T>::size;
        using SeqList<T>::capacity;

    private:
        bool isUnequalExist(const vector& other);
    };

    // 函数定义
    template<class T>
    vector<T>::vector() : SeqList<T>() {}

    template<class T>
    vector<T>::vector(const int _size) : 
            SeqList<T>() {
        if (_size <= 0) 
            return;
        capacity = DEFAULT_CAPACITY;
        size = _size;
        while (_size > capacity) {
            capacity *= 2;
        }
        arr = new T[capacity];
    }

    template<class T>
    vector<T>::vector(const int _size, const T& _value) : 
            SeqList<T>() {
        if (_size <= 0)
            return;
        capacity = DEFAULT_CAPACITY;
        size = _size;
        while (_size > capacity) {
            capacity *= 2;
        }
        arr = new T[capacity];
        for (int i = 0; i < _size; i++) {
            arr[i] = _value;
        }
    }

    template<class T>
    vector<T>::vector(const vector& other) : 
            SeqList<T>() {
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }

    template<class T>
    template<class Iterator>
    vector<T>::vector(const Iterator& _begin, const Iterator& _end) {
        for (auto it = _begin; it != _end; ++it) {
            this->push_back(*it);
        }
    }

    template<class T>
    void vector<T>::push_back(const T& _value) {
        if (size == capacity) {
            this->expand(); // 扩容
        }
        arr[size++] = _value;
    }

    template<class T>
    void vector<T>::pop_back() {
        size--;
    }

    template<class T>
    bool vector<T>::empty() {
        return (size == 0) ? true : false;
    }

    template<class T>
    void vector<T>::reserve(const int _size) {
        if (capacity >= _size) {
            return;
        }
        while (capacity < _size) {
            this->expand();
        }
    }

    template<class T>
    void vector<T>::swap(vector<T>& other) {
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
        std::swap(arr, other.arr);
    }

    template<class T>
    const T& vector<T>::at(const int _index) const {
        if (_index < 0 || _index >= size) {
            throw std::out_of_range("Stack index out of range");
        }
        return arr[_index];
    }

    template<class T>
    const T& vector<T>::front() const {
        if (arr == nullptr) {
            throw std::underflow_error("front not exists");
        }
        return arr[0];
    }

    template<class T>
    const T& vector<T>::back() const {
        if (arr == nullptr) {
            throw std::underflow_error("front not exists");
        }
        return arr[size - 1];
    }

    template<class T>
    T* vector<T>::data() {
        return arr;
    }

    template<class T>
    const int vector<T>::get_size() const {
        return size;
    }

    template<class T>
    const int vector<T>::get_capacity() const {
        return capacity;
    }

    template<class T>
    void vector<T>::shrink_to_fit() {
        while (size <= capacity / 2) {
            capacity /= 2;
        }
        T* newArr = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[]arr;
        arr = newArr;
    }

    template<class T>
    T& vector<T>::operator[](const int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Stack index out of range");
        }
        return arr[index];  
    }

    template<class T>
    vector<T>& vector<T>::operator=(const vector<T>& other) {
        if (*this == other) {
            return *this;
        }
        if (arr != nullptr) {
            this->clear();
        }
        size = other.size;
        capacity = other.capacity;
        arr = new T[capacity];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
        return *this;
    }

    template<class T>
    bool vector<T>::operator==(const vector<T>& other) {
        return (size == other.size) && (capacity == other.capacity) && !isUnequalExist(other);    
    }

    template<class T>
    bool vector<T>::operator!=(const vector<T>& other) {
        return !(*this == other);
    }

    template<class T>
    bool vector<T>::isUnequalExist(const vector<T>& other) {
        for (int i = 0; i < size; i++) {
            if (arr[i] != other.arr[i]) {
                return true;
            }
        }
        return false;
    }

    // template<class T>
    // vector<T>::iterator vector<T>::begin() {
    //     return vector<T>::iterator(0, size, arr);
    // } 

    // template<class T>
    // vector<T>::iterator vector<T>::end() {
    //     return vector<T>::iterator(size, size, arr);
    // }

    // template<class T>
    // vector<T>::iterator vector<T>::iter_at(int _index) {
    //     return vector<T>::iterator(_index, size, arr);
    // }

    // template<class T>
    // void vector<T>::erase(vector<T>::iterator _start, vector<T>::iterator _end) {
    //     int start = _start.getIndex();
    //     int end;
    //     end = ((end = _end.getIndex()) == -1) ? size : end;
    //     int len = end - start;
    //     for (int i = end; i < size; i++) {
    //         arr[i - len] = arr[i];
    //     }
    //     size -= len;
    // }

    // template<class T>
    // void vector<T>::erase(vector<T>::iterator pos, int len) {
    //     vector<T>::iterator start = pos;
    //     vector<T>::iterator end = this->end();
    //     if (pos.getIndex() + len < size) {
    //         end = vector<T>::iterator(pos.getIndex() + len, size, arr);
    //     }
    //     this->erase(start, end);
    // }

    // template<class T>
    // void vector<T>::insert(vector<T>::iterator pos, const T& _value) {
    //     int index = pos.getIndex();
    //     if (index == -1) {
    //         throw std::out_of_range("end iterator is passed");
    //     }
    //     if (size + 1 > capacity) {
    //         this->expand();
    //     }
    //     for (int i = size - 1; i >= index; i--) {
    //         arr[i + 1] = arr[i];
    //     }
    //     arr[index] = _value;
    //     size++;
    // }

    // template<class T>
    // void vector<T>::insert(vector<T>::iterator pos, int n, const T& _value) {
    //     for (int i = 0; i < n; i++) {
    //         this->insert(pos, _value);
    //         ++pos;
    //     }
    // }
}

using namespace std;

int main() {
    int n;
    cin >> n;
    MyStl::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    MyStl::vector<int> res(n);
    int cnt = 0;
    for (int h = 0; h < n; h++) {
        for (int i = 1; i < n - h; i++) {
            if (v[i + h] > v[h]) {
                res[cnt] = i;
                break;
            }
        }
        cnt++;
    }
    for (int i = 0; i < res.get_size(); i++) {
        cout << res[i] << " ";
    }
    return 0;
}