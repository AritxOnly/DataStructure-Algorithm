#include <cstddef>

template<class T>
class SeqList {
public:
    SeqList();
    SeqList(const SeqList<T>& other);
    SeqList(size_t size, T value = T());
    ~SeqList();

    void insert(size_t index, const T& value);
    T& operator[](size_t index);
    void qsort();

private:
    T* arr;
    int size;
    int capacity = 100;

    void expand();
};