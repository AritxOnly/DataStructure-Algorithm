/**
 * LeetCode 2181. Merge Nodes in Between Zeros
 * https://leetcode.com/problems/merge-nodes-in-between-zeros/
 * Problem Solved with O(n) Time Complexity
 */

#include <iostream>

typedef struct ListNode ListNode;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* n) : val(x), next(n) {}
};

class Solution {
public:
    ListNode* mergeNodes(ListNode* head) {
        ListNode* newHead = new ListNode(-1);
        // 遍历链表
        ListNode* p = head;
        ListNode* q = newHead;
        bool passZero = true;
        int sum = 0;
        while (p != nullptr) {
            passZero = (p->val == 0) ? true : false;
            if (passZero) {
                if (sum != 0) {
                    q->next = new ListNode(sum);
                    q = q->next;
                    sum = 0;
                }
            } else {
                sum += p->val;
            }
            p = p->next;
        }
        return newHead->next;
    }
};

int main() {
    Solution s;
    ListNode* head = new ListNode(0, 
            new ListNode(3, 
            new ListNode(1, 
            new ListNode(0, 
            new ListNode(4, 
            new ListNode(5, 
            new ListNode(2, 
            new ListNode(0))))))));

    ListNode* newHead = s.mergeNodes(head);
    while (newHead != nullptr) {
        std::cout << newHead->val << " ";
        newHead = newHead->next;
    }
    return 0;
}