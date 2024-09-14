#ifndef __SEQLIST_H__
#define __SEQLIST_H__

const long long MAX_SIZE = 2147483647;
const int DEFAULT_CAPACITY = 100;

template<class T>
class SeqList {
public:
    SeqList();
    virtual ~SeqList();

protected:
    T* arr;
    int size;
    int capacity;

    void expand();  // 扩容
};

#endif