#include <iostream>
#include <vector>
#include <tuple>
#include <memory>

using namespace std;

/*
* Fenwick Tree之實作，採用Array
*/
template<typename T>
class fenwickTree
{
public:
    fenwickTree(vector<T> &_data) : data(_data), tree(data.size() + 1, 0)
    {
        buildTree();
    }

    // 更新第index位置的值為val
    void update(int index, T val)
    {
        T diff = val - data[index];
        data[index] = val;
        for (int i = index + 1; i < tree.size(); i += lowbit(i))
            tree[i] += diff;
    }

    // 查詢前index個元素的和
    T query(int index)
    {
        T sum = 0;
        for (int i = index + 1; i > 0; i -= lowbit(i))
            sum += tree[i];
        return sum;
    }

    T query(int i_1, int i_2)
    {
        return query(i_2) - query(i_1 - 1);
    }

    void print()
    {
        for (auto item : tree)
            cout << item << " ";
        cout << endl;
    }

private:
    vector<T> data;
    vector<T> tree;

    // 建立Fenwick Tree / Binary Indexed Tree，請參考花花刷题找工作 SP3
    // 主要是用index的2進位作為父子連結的關係來建立樹
    void buildTree()
    {
        for (int i = 1; i < tree.size(); ++i)
            for (int j = i; j < tree.size(); j += lowbit(j))
                tree[j] += data[i - 1];
    }
    
    inline int lowbit(int index)
    {
        return index & (-index);
    }
};

/*
* 線段樹之實作，採用array
*/
template <class T>
class segmentTree
{
public:
    segmentTree(vector<T> &_data, T (*_merge)(T &, T &)) : data(_data), tree(_data.size() * 4, 0), merge(_merge)
    {
        if (data.size() != 0)
            buildTree(0, 0, data.size() - 1);
    }

    // 返回complete binary tree中左子樹的根節點之索引
    int leftChild(int index)
    {
        return index * 2 + 1;
    }

    // 返回complete binary tree中右子樹的根節點之索引
    int rightChild(int index)
    {
        return index * 2 + 2;
    }

    // 返回data區間[queryL, ..., queryR]中相對應merge的值
    T query(int queryL, int queryR)
    {
        return query(0, 0, data.size() - 1, queryL, queryR);
    }
    
    // 將data中index的位置，更新為element
    void set(int index, T element)
    {
        data[index] = element;
        set(0, 0, data.size() - 1, index, element);
    }

    void print()
    {
        for(auto item:data)
            cout << item << " ";
        cout << endl;
    }

    void print_Tree()
    {
        for (auto item : tree)
            cout << item << " ";
        cout << endl;
    }

private:
    vector<T> data; // 
    vector<T> tree;
    T (*merge)(T &, T &);

    // 創建以nodeIndex為根節點的線段樹
    void buildTree(int nodeIndex, int l, int r)
    {
        if (l == r)
        {
            tree[nodeIndex] = data[l];
            return;
        }
        int &&leftTreeIndex = leftChild(nodeIndex);
        int &&rightTreeIndex = rightChild(nodeIndex);
        int mid = l + (r - l) / 2;
        buildTree(leftTreeIndex, l, mid);
        buildTree(rightTreeIndex, mid + 1, r);
        tree[nodeIndex] = merge(tree[leftTreeIndex], tree[rightTreeIndex]);
        return;
    }

    // 在以nodeIndex為根節點的線段樹中[l, ..., r]的範圍裡，查詢data區間[queryL, ..., queryR]相對應merge的值
    T query(int nodeIndex, int l, int r, int queryL, int queryR)
    {
        if (l == queryL && r == queryR)
            return tree[nodeIndex];
        int &&leftTreeIndex = leftChild(nodeIndex);
        int &&rightTreeIndex = rightChild(nodeIndex);
        int mid = l + (r - l) / 2;
        if (queryL >= mid + 1)
            return query(rightTreeIndex, mid + 1, r, queryL, queryR);
        else if (queryR <= mid)
            return query(leftTreeIndex, l, mid, queryL, queryR);
        else
        {
            T &&leftResult = query(leftTreeIndex, l, mid, queryL, mid);
            T &&rightResult = query(rightTreeIndex, mid + 1, r, mid + 1, queryR);
            return merge(leftResult, rightResult);
        }
    }

    // 在以nodeIndex為根節點的線段樹中修改dataIndex的值為element
    void set(int nodeIndex, int l, int r, int dataIndex, T element)
    {
        if(l == r)
        {
            tree[nodeIndex] = element;
            return;
        }
        int &&leftTreeIndex = leftChild(nodeIndex);
        int &&rightTreeIndex = rightChild(nodeIndex);
        int mid = l + (r - l) / 2;

        if (dataIndex >= mid + 1)
            set(rightTreeIndex, mid + 1, r, dataIndex, element);
        else // dataIndex <= mid
            set(leftTreeIndex, l, mid, dataIndex, element);
        
        // 回去的時候記得父節點會受到子節點之影響
        tree[nodeIndex] = merge(tree[leftTreeIndex], tree[rightTreeIndex]);
        return;
    }
};

template <typename T>
T merge(T & a, T & b)
{
    return a + b;
}

/*
* 線段樹之實作，採用linked-list
*/
class Node
{
public:
    int start;
    int end;
    int sum;
    Node *left;
    Node *right;
    Node(int _start, int _end, int _sum, Node *_left = nullptr, Node *_right = nullptr) : start(_start), end(_end), sum(_sum), left(_left), right(_right) {}

    // = delete的用意是告訴compiler下面這兩個：複製建構子、賦值運算子不可以被使用
    Node(const Node &) = delete;
    Node &operator=(const Node &) = delete;

    ~Node()
    {
        delete left;
        delete right;
        left = right = nullptr;
    }
};

class segmentTree_link
{
private:
    unique_ptr<Node> head;

    Node *buildTree(int start, int end, vector<int> &data)
    {
        if (start == end)
            return new Node(start, end, data[start]);
        int mid = start + (end - start) / 2;
        auto left = buildTree(start, mid, data);
        auto right = buildTree(mid + 1, end, data);
        return new Node(start, end, left->sum + right->sum, left, right);
    }

    void update(Node *root, int i, int val)
    {
        if (root->start == i && root->end == i)
        {
            root->sum = val;
            return;
        }
        int mid = root->start + (root->end - root->start) / 2;
        if (i <= mid)
            update(root->left, i, val);
        else
            update(root->right, i, val);
        root->sum = root->left->sum + root->right->sum;
    }

    int query(Node *root, int i, int j)
    {
        if (i == root->start && j == root->end)
            return root->sum;
        int mid = root->start + (root->end - root->start) / 2;
        if (j <= mid)
            return query(root->left, i, j);
        else if (i > mid)
            return query(root->right, i, j);

        return query(root->left, i, mid) + query(root->right, mid + 1, j);
    }

public:
    segmentTree_link(vector<int> &data)
    {
        if (data.size() != 0)
            head.reset(buildTree(0, data.size() - 1, data));
    }

    void set(int i, int val)
    {
        update(head.get(), i, val);
    }

    int query(int i, int j)
    {
        return query(head.get(), i, j);
    }
};

class NumArray
{
private:
    // segmentTree<int> seg;

    // fenwickTree<int> fenwick;

    segmentTree_link seg;

public:
    NumArray(vector<int> &nums) : seg{nums} // fenwick{nums} // seg{nums, merge}
    {
        // fenwick.print();
    }

    void update(int i, int val)
    {
        seg.set(i, val);

        // fenwick.update(i, val);
    }

    int sumRange(int i, int j)
    {
        return seg.query(i, j);
        // return fenwick.query(i, j);
    }
};

int main()
{
    vector<int> nums{7, 2, 7, 2, 0};
    NumArray q{nums};
    cout << (q.sumRange(0, 3) == 18 ? "Success" : "Fail") << endl;
    q.update(4, 6);
    q.update(0, 2);
    q.update(0, 9);
    cout << (q.sumRange(4, 4) == 6 ? "Success" : "Fail") << endl;
    q.update(3, 8);
    cout << (q.sumRange(0, 4) == 32 ? "Success" : "Fail") << endl;
    q.update(4, 1);
    cout << (q.sumRange(0, 3) == 26 ? "Success" : "Fail") << endl;
    cout << (q.sumRange(0, 4) == 27 ? "Success" : "Fail") << endl;
    q.update(0, 4);
}