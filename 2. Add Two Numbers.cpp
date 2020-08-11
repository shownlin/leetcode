#include <iostream>

using std::cout;


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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode res{}, *p = &res;
        int carry{ 0 };
        while(l1 || l2 || carry)
        { 
            int sum = (l1==nullptr?0:l1->val) + (l2==nullptr?0:l2->val) + carry;
            p = p->next = new ListNode(sum % 10);
            if (l1)
                l1 = l1->next;
            if(l2)
                l2 = l2->next;
            carry = sum / 10;
        }
        return res.next;
    }
};

int main()
{
    ListNode *list1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode *list2 = new ListNode(5, new ListNode(6, new ListNode(4)));
    Solution sol;
    ListNode *ans = sol.addTwoNumbers(list1, list2);
    for (auto it = ans; it != nullptr; it = it->next)
    {
        cout << it->val << " ";
    }
    delete list1;
    delete list2;
    return 0;
}

