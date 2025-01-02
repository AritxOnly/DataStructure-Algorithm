#ifndef __GENERAL_LIST_H__
#define __GENERAL_LIST_H__

#include <iostream>
template<class Tp>
struct GenListNode {
    int utype;  // = 0/1/2
    GenListNode<Tp>* tlink; // 同层下一节点的指针
    union {
        int ref;    // 引用计数
        Tp value;   // 值
        GenListNode<Tp>* hlink; // 子表指针
    } info;
    GenListNode<Tp>() : utype(0), tlink(nullptr), info(0) {}
    GenListNode<Tp>(const GenListNode<Tp>& other) {
        utype = other.utype;
        tlink = other.tlink;
        info = other.info;
    }
};

template<class Tp>
class GenList {
public:
    // 类型别名
    using NodePtr = GenListNode<Tp>*;
    using Node = GenListNode<Tp>;
    using NodeRef = GenListNode<Tp>&;
    using ListPtr = GenList<Tp>*;
    using List = GenList<Tp>;
    using ListRef = GenList<Tp>&;

    GenList();
    ~GenList();
    NodeRef head();
    ListRef tail();
    NodePtr first();
    NodePtr next(NodePtr elm);
    void copy(ListRef other);
    int length();
    int depth();

private:
    NodePtr fst;
    NodePtr copy(const NodePtr ls);
    int length(const NodePtr ls);
    int depth(const NodePtr ls);
    bool equal(const NodePtr s, const NodePtr t);
    void remove(NodePtr ls);
};

template<class Tp>
GenList<Tp>::GenList() {
    NodePtr first = new Node;
    if (first == nullptr) {
        std::cerr << "Allocation failed\n";
    }
    fst = first;
}

template<class Tp>
GenListNode<Tp>& GenList<Tp>::head() {
    if (fst->tlink == nullptr)  return Node();
    return Node(*fst);
}

template<class Tp>
GenList<Tp>& GenList<Tp>::tail() {
    if (fst->tlink == nullptr)  return Node();
    ListPtr res = new List;
    res->fst->utype = 0;
    res->fst->info.ref = 0;
    res->fst->tlink = copy(fst->tlink->tlink);
    return *res;
}

template<class Tp>
GenListNode<Tp>* GenList<Tp>::first() {
    if (fst->tlink == nullptr)  return nullptr;
    return fst->tlink;
}

template<class Tp>
GenListNode<Tp>* GenList<Tp>::next(GenListNode<Tp>* elm) {
    return elm->tlink;
}


#endif