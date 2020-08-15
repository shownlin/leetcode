#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr){}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right){}
    ~TreeNode()
    {   
        if (left)
            delete left;
        if (right)
            delete right;
    }
 };

 class Solution
 {
 public:
    int pseudoPalindromicPaths(TreeNode *root){
        // 思路：DFS遍歷整棵樹，運用state(bit string)紀錄0~9分別為odd還是even，當達到leaf時可允許state有其中一個bit為1，其他皆為0
        function<int(TreeNode *, int)> dfs = [&](TreeNode *node, int state) {
            if (!node)
                return 0;
            state ^= 1 << node->val;
            // 可允許有一個bit為1，根據2's complement
            // 一個正整數與其相對應的負數剛好是所有bit取反再+1
            // 兩者取&會留下最低位為1之bit
            // 此時拿原本的bit string去減，若為0則知道該bit string僅有一個bit為1
            // 若不等於0代表除了該最低位為1之bit外，bit string中仍有其他bits為1
            if (!node->left && ! node->right && !(state - (state & -state)))
                return 1;
            else
                return dfs(node->left, state) + dfs(node->right, state);
        };

        return dfs(root, 0);
    }
 };

int main()
{
    TreeNode *root1 = new TreeNode(2, new TreeNode(3, new TreeNode(3), new TreeNode(1)), new TreeNode(1, nullptr, new TreeNode(1)));
    TreeNode *root2 = new TreeNode(2, new TreeNode(1, new TreeNode(1), new TreeNode(3, nullptr, new TreeNode(1))), new TreeNode(1));
    TreeNode *root3 = new TreeNode(9);
    vector<pair<TreeNode*, int>> q{{root1, 2}, {root2, 1}, {root3, 1}};
    Solution sol;
    for (auto i:q)
    {
        cout << ((i.second == sol.pseudoPalindromicPaths(i.first)) ? "Success" : "Failure") << " ";
        // cout << sol.pseudoPalindromicPaths(i.first) << " ";
    }
    delete root1;
    delete root2;
    delete root3;
}