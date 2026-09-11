/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k == 1) return head;
        ListNode dummy(0);
        dummy.next = head;
        ListNode* prevGroupEnd = &dummy;

        while (true) {
            ListNode* kth = prevGroupEnd;
            for (int i = 0; i < k && kth; i++) {
                kth = kth->next;
            }
            if (!kth) break; 
            ListNode* groupStart = prevGroupEnd->next;
            ListNode* curr = groupStart->next;
            ListNode* prev = groupStart;

            for (int i = 1; i < k; i++) {
                ListNode* next = curr->next;
                curr->next = prevGroupEnd->next;
                prevGroupEnd->next = curr;
                curr = next;
            }
            groupStart->next = curr;
            prevGroupEnd = groupStart;
        }

        return dummy.next;
    }
};