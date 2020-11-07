#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <memory>
using namespace std;

class Node
{
public:
    int start;  // 區間起始點：已經離散化
    int end;    // 區間結束點：已經離散化
    long long len;    // 區間長度
    int cnt;    // 計算某個區間被覆蓋(掃描線重複掃到)的次數，進入時增加一次，離開時被扣掉一次
    Node * left;
    Node * right;
    Node(int _start, int _end, Node *_left = nullptr, Node *_right = nullptr, int _len = 0, int _cnt = 0) : start(_start), end(_end), left(_left), right(_right), len(_len), cnt(_cnt) {}

    // = delete的用意是告訴compiler下面這兩個：複製建構子、賦值運算子不可以被使用
    Node(const Node &) = delete;
    Node & operator=(const Node &) = delete;

    ~Node()
    {
        delete left;
        delete right;
        left = right = nullptr;
    }
};

class SegmentTree
{
private:
    unique_ptr<Node> head;
    unordered_map<int, int> discrete_X, orig_X;

    // 建立線段樹，最細區間為[x, x + 1]，但為了update長度時的方便(遞迴中有 root->len = root->left->len + root->right->len 這麼一句)
    // 故在最細區間之下仍建立dummy leaves為[x, x]和[x+1, x+1]，長度皆為0
    // 另外，樹的分裂方式為 左：[i, mid] 右：[mid, j]，mid是重疊的
    Node * buildTree(int start, int end)
    {
        Node *left, *right;
        if (start + 1 == end)
        {
            left = new Node(start, start);
            right = new Node(end, end);
        }
        else
        {
            int mid = start + ((end - start) >> 1);
            left = buildTree(start, mid);
            right = buildTree(mid, end);
        }
        return new Node(start, end, left, right);
    }

    // 更新i到j被覆蓋次數，掃描線遇到矩形的底邊+1，遇到矩形的頂邊-1，同時計算每個區間對應的長度
    void update(Node * root, int i, int j, int type)
    {
        if (i >= j)
            return;
        if (root->start == i && root->end == j)
            root->cnt += type;
        else
        {
            int mid = root->start + ((root->end - root->start) >> 1);
            // 跟一般的線段樹不一樣，我們更新的是一個「區間」，而非一個點，要特別注意此種情況：
            // 假設[mid, j] = [1, 3]，但要更新的區間是[i, j] = [2, 3]，所以這邊需要用max()比較mid和i之大小
            update(root->left, i, min(mid, j), type);
            update(root->right, max(mid, i), j, type);
        }

        // 更新此節點之長度，如果 root->cnt > 0 則代表恰有一段起點為root->start和終點為root->end的線段被掃描線進入，則它的長度就是這個區間本身的長度
        if (root->cnt > 0)
        {
            root->len = orig_X[root->end] - orig_X[root->start];
        }
        // 若 root->cnt == 0 則代表這個區間的應該是由它的子區間長度構成，也就是說這個區間中不是完整的一條直線，而是一段一段的，故由左右子樹的長度來加總
        else
            root->len = root->left->len + root->right->len;
    }

public:
    SegmentTree(unordered_map<int, int> &_discrete_X, unordered_map<int, int> &_orig_X) : discrete_X(_discrete_X), orig_X(_orig_X)
    {
        head.reset(buildTree(0, discrete_X.size() - 1));
    }

    void update(int i, int j, int type)
    {
        update(head.get(), discrete_X[i], discrete_X[j], type);
    }

    // 注意：返回long long避免運算式溢位
    // 每次查詢一定都是查詢[最左邊的x, 最右邊的x]，因為我們會把所有被覆蓋到的子區間之總和長度更新到root
    long long query()
    {
        return head->len;
    }

};

class Solution
{
public:
    int rectangleArea(vector<vector<int>> &rectangles)
    {
        const int OPEN = 1, CLOSE = -1;
        vector<vector<int>> events; // 每次遇到一條矩形的底邊或頂邊就是一次event，經過sort以後就是掃描線掃描之順序
        set<int> xs;    // 使用set是為了讓它按照x座標自動排序

        for (auto & rec : rectangles)
        {
            // 掃描線由底部往頂端掃，按y軸遞增排序先
            // rec[0]: 左下角的x，rec[1]: 左下角的y
            // rec[2]: 右上角的x，rec[3]: 右上角的y
            // 遇到矩形下方的邊代表進入：OPEN，遇到矩形上方的邊代表離開：CLOSE
            events.push_back({rec[1], OPEN, rec[0], rec[2]});
            events.push_back({rec[3], CLOSE, rec[0], rec[2]});

            // 插入x座標
            xs.insert(rec[0]);
            xs.insert(rec[2]);
        }

        // 按y軸排序
        sort(events.begin(), events.end(), [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });

        // Xi用來離散化X座標(用來建立線段樹)，orig_X則是把離散化後的X轉回原本的X(用來計算長度)
        unordered_map<int, int> Xi, orig_X;
        int i = 0;
        for (auto x: xs)
        {
            orig_X[i] = x;
            Xi[x] = i++;
        }

        SegmentTree activate{Xi, orig_X};
        long long area = 0;
        int cur_y = 0;
        int len = 0;
        for (auto e: events)
        {
            // 面積計算方式：整個區域(root)返回的長度 * (這一次的y - 上一次的y)(也就是高度) = 這一次需要加上的面積
            area += (activate.query() * (e[0] - cur_y)) % static_cast<long long>(1e9 + 7);
            // 更新被覆蓋到的區間[e[2], e[3]]，為一個左閉右閉的區間，並且更新長度，用e[1]來決定是進入還是離開一個矩形
            activate.update(e[2], e[3], e[1]);
            cur_y = e[0];
        }
        return area % static_cast<long long>(1e9 + 7);
    }
};

int main()
{
    Solution sol;
    // vector<vector<int>> q{{0, 0, 2, 2 }, { 1, 0, 2, 3 }, { 1, 0, 3, 1 }};
    // cout << (sol.rectangleArea(q) == 6 ? "Success" : "Fail") << endl;
    // vector<vector<int>> q {{ 0, 0, 1000000000, 1000000000 }};
    // cout << (sol.rectangleArea(q) == 49 ? "Success" : "Fail") << endl;
    // vector<vector<int>> q{{0, 0, 1, 1}, {2, 2, 3, 3}};
    // cout << (sol.rectangleArea(q) == 2 ? "Success" : "Fail") << endl;
    vector<vector<int>> q{{224386961, 128668997, 546647847, 318900555}, {852286866, 238086790, 992627088, 949888275}, {160239672, 137108804, 398130330, 944807066}, {431047948, 462092719, 870611028, 856851714}, {736895365, 511285772, 906155231, 721626624}, {289309389, 607009433, 558359552, 883664714}, {780746435, 397872372, 931219192, 863727103}, {573523994, 124874359, 889018012, 471879750}, {619886375, 149607927, 727026507, 446976526}, {51739879, 716225241, 115331335, 785850603}, {171077223, 267051983, 548436248, 349498903}, {314437215, 169054168, 950814572, 481179241}, {64126215, 646689712, 595562376, 829164135}, {926011655, 481539702, 982179297, 832455610}, {40370235, 231510218, 770233582, 851797196}, {292546319, 45032676, 413358795, 783606009}, {424366277, 369838051, 453541063, 777456024}, {211837048, 142665527, 217366958, 952362711}, {228416869, 402115549, 672143142, 644930626}, {755018294, 194555696, 846854520, 939022548}, {192890972, 586071668, 992336688, 759060552}, {127869582, 392855032, 338983665, 954245205}, {665603955, 208757599, 767586006, 276627875}, {260384651, 10960359, 736299693, 761411808}, {46440611, 559601039, 911666265, 904518674}, {54013763, 90331595, 332153447, 106222561}, {73093292, 378586103, 423488105, 826750366}, {327100855, 516514806, 676134763, 653520887}, {930781786, 407609872, 960671631, 510621750}, {35479655, 449171431, 931212840, 617916927}};
    cout << (sol.rectangleArea(q) == 862275791 ? "Success" : "Fail") << endl;
    }