#include <iostream>
#include <vector>
#include <utility>

using std::cout;
using std::vector;
using std::swap;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        //檢查有沒有空的，可以加快一點速度
        if (!l1 || !l2)
            return l1?l1:l2;

        ListNode head{ 0 }, *tail = &head;
        while (l1 && l2)
        {   
        
            if (l1->val > l2->val)
                swap(l1,l2);
            tail = tail->next = l1;
            l1 = l1->next;
        }
        //總會有一個list先變成空的
        tail->next = l1?l1:l2;
        return head.next;
    }

};

int main()
{
    ListNode *list1 = new ListNode(1, new ListNode(2, new ListNode(4)));
    ListNode *list2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    Solution sol;
    ListNode *ans = sol.mergeTwoLists(list1, list2);
    for (auto it = ans; it != nullptr; it = it->next)
    {
        cout << it->val << " ";
    }
    delete list1;
    delete list2;
    return 0;
}

