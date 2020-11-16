#include <iostream>
#include <vector>

using std::cout;
using std::vector;

// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// list之間兩兩合併，while第一圈合併第i條和第i+1條串列，while第二圈合併第i條和第i+2條串列，以此類推，直到全部合併到list[0]為止。
class Solution {
public:
    // Divide and conquer
    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        const int K = lists.size();
        int interval = 1;
        while (interval < K)
        {
            // i每次加上interval * 2，因為list[i]和list[i + interval]已經被合併到list[i]去了
            for (int i = 0; i < K - interval; i += interval * 2)   
            {
                lists[i] = merge2List(lists[i], lists[i + interval]);
            }
            interval *= 2;
        }
        //這邊要非常注意，有可能給空的lists
        return K > 0 ? lists[0] : nullptr;
    }

    ListNode* merge2List(ListNode* l1, ListNode* l2)
    {
        //檢查有沒有空的，可以加快一點速度
        if (!l1 || !l2)
            return l1 ? l1 : l2;

        // 先創一個節點的頭(dummy node)，但是這個節點不要return回去
        ListNode head{ 0 }, *tail = &head;
        
        // 從頭開始合併，直到某個list走到最後面
        while (l1 && l2)
        {   
        
            if (l1->val < l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
            
        }
        //總會有一個list先變成空的
        tail->next = l1 ? l1 : l2;
        // return的是head的下一個，頭我們不要
        return head.next;
    }

};

int main()
{
    ListNode *list1 = new ListNode(1, new ListNode(4, new ListNode(5)));
    ListNode *list2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    ListNode *list3 = new ListNode(2, new ListNode(6));
    vector<ListNode*> lists{ list1, list2, list3 };
    Solution sol;
    ListNode *ans = sol.mergeKLists(lists);
    // ListNode *ans = sol.merge2List(list1, list2);
    for (auto it = ans; it != nullptr; it = it->next)
    {
        cout << it->val << " ";
    }
    delete list1;
    delete list2;
    delete list3;
    return 0;
}

