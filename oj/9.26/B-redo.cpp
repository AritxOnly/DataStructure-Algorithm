#include <climits>
#include <cstdio>
#include <cstring>

typedef unsigned long long ULL;

const int MAX_N = 1000010;
const int HASH_SIZE = 1000003;  // 一个大于 1e6 的质数
const int MAX_NODES = 2000010;

int n;
ULL a;

// 最小堆的实现
ULL heap[MAX_N];
int heap_size = 0;

void heap_push(ULL x) {
    heap[++heap_size] = x;
    int i = heap_size;
    while (i > 1 && heap[i] < heap[i >> 1]) {
        ULL temp = heap[i];
        heap[i] = heap[i >> 1];
        heap[i >> 1] = temp;
        i >>= 1;
    }
}

ULL heap_pop() {
    ULL min_element = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while ((i << 1) <= heap_size) {
        int smallest = i << 1;
        if (smallest + 1 <= heap_size && heap[smallest + 1] < heap[smallest]) {
            smallest++;
        }
        if (heap[i] > heap[smallest]) {
            ULL temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return min_element;
}

// 哈希集合的实现
struct Node {
    ULL value;
    int next;
} nodes[MAX_NODES];
int hash_table[HASH_SIZE];
int node_count = 0;

bool insert_to_hash(ULL x) {
    int hash_index = x % HASH_SIZE;
    int idx = hash_table[hash_index];
    while (idx != -1) {
        if (nodes[idx].value == x) {
            return false;  // 已存在于哈希集合中
        }
        idx = nodes[idx].next;
    }
    nodes[node_count].value = x;
    nodes[node_count].next = hash_table[hash_index];
    hash_table[hash_index] = node_count++;
    return true;
}

int main() {
    scanf("%llu %d", &a, &n);

    memset(hash_table, -1, sizeof(hash_table));
    heap_size = 0;
    node_count = 0;

    heap_push(a);
    insert_to_hash(a);

    int result_count = 0;
    ULL x;

    while (result_count < n) {
        x = heap_pop();
        result_count++;
        if (result_count == n) {
            printf("%llu\n", x);
            break;
        }

        if (x <= (ULLONG_MAX - 1) / 2) {
            ULL fx = 2 * x + 1;
            if (insert_to_hash(fx)) {
                heap_push(fx);
            }
        }

        if (x <= (ULLONG_MAX - 1) / 3) {
            ULL gx = 3 * x + 1;
            if (insert_to_hash(gx)) {
                heap_push(gx);
            }
        }
    }

    return 0;
}