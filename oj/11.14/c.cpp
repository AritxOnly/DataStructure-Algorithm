#include <iostream>

using namespace std;

// 将 MaxHeap 修改为 MinHeap
template<class T>
class MinHeap {
public:
    struct HeapNode {
        T val;
        int pos;
    };

private:
    HeapNode* heap;
    int size;
    int capacity;

    int parent(int idx) {
        return (idx - 1) / 2;
    }

    int leftChild(int idx) {
        return idx * 2 + 1;
    }

    int rightChild(int idx) {
        return idx * 2 + 2;
    }
    
    void heapifyUp(int idx) {
        while (idx > 0 && heap[parent(idx)].val > heap[idx].val) { // 修改比较符号
            HeapNode temp = heap[parent(idx)];
            heap[parent(idx)] = heap[idx];
            heap[idx] = temp;
            idx = parent(idx);
        }
    }

    void heapifyDown(int idx) {
        int minIndex = idx;
        int l = leftChild(idx);
        if (l < size && heap[l].val < heap[minIndex].val) // 修改比较符号
            minIndex = l;
        int r = rightChild(idx);
        if (r < size && heap[r].val < heap[minIndex].val) // 修改比较符号
            minIndex = r;
        if (idx != minIndex) {
            HeapNode temp = heap[idx];
            heap[idx] = heap[minIndex];
            heap[minIndex] = temp;
            heapifyDown(minIndex);
        }
    }

public:
    MinHeap(int cap) : heap(new HeapNode[cap]), size(0), capacity(cap) {}

    ~MinHeap() { delete[]heap; }

    void insert(T value, int position) {
        if (size == capacity) {
            // 扩容
            capacity *= 2;
            HeapNode* newHeap = new HeapNode[capacity];
            for (int i = 0; i < size; i++)
                newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }
        heap[size].val = value;
        heap[size].pos = position;
        heapifyUp(size);
        size++;
    }

    HeapNode extractMin() {
        if (size == 0)
            return {0, 0};
        HeapNode result = heap[0];
        size--;
        heap[0] = heap[size];
        heapifyDown(0);
        return result;
    }

    bool isEmpty() {
        return size == 0;
    }
};

template<class T>
struct AdjustedRoom {
    T value;      // 房间的影响值
    int position; // 房间的位置（编号）
};

// 归并排序实现
template<class T>
void merge(AdjustedRoom<T>* arr, int l, int m, int r, AdjustedRoom<T>* temp) {
    int i = l;
    int j = m + 1;
    int k = l;
    while (i <= m && j <= r) {
        if (arr[i].position <= arr[j].position)
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i <= m)
        temp[k++] = arr[i++];
    while (j <= r)
        temp[k++] = arr[j++];
    for (int t = l; t <= r; t++)
        arr[t] = temp[t];
}

template<class T>
void mergeSort(AdjustedRoom<T>* arr, int l, int r, AdjustedRoom<T>* temp) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, temp);
    mergeSort(arr, m + 1, r, temp);
    merge(arr, l, m, r, temp);
}

int main() {
    int n;
    cin >> n;
    int* nums = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    long long health = 1; // 修改为 long long，防止溢出
    int adjusts = 0;
    int adj = 0;
    MinHeap<int> mh(100); // 使用 MinHeap
    AdjustedRoom<int>* ar = new AdjustedRoom<int>[n];

    for (int i = 0; i < n; i++) {
        health += nums[i];
        if (nums[i] < 0) {
            mh.insert(nums[i], i);
        }
        while (health < 1) {
            if (mh.isEmpty()) {
                cout << -1 << endl;
                delete[] nums;
                delete[] ar;
                return 0;
            }
            MinHeap<int>::HeapNode removed = mh.extractMin(); // 提取最小值
            health -= removed.val; // 移除影响值（因为是负数，所以减去）
            ar[adj].value = removed.val;
            ar[adj].position = removed.pos;
            adj++;
            adjusts++;
        }
    }

    if (adj > 0) {
        AdjustedRoom<int>* tmp = new AdjustedRoom<int>[adj];
        mergeSort(ar, 0, adj - 1, tmp); // 修正范围为 adj - 1
        delete[] tmp;
    }

    for (int i = 0; i < adj; i++) {
        health += ar[i].value;
        if (health < 1) {
            cout << -1 << endl;
            delete[] nums;
            delete[] ar;
            return 0;
        }
    }

    cout << adjusts << endl;
    delete[] nums;
    delete[] ar;

    return 0;
}