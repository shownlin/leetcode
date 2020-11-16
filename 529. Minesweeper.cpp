#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<vector<char>> updateBoard(vector<vector<char>> &board, vector<int> &click)
    {
        if(board[click[0]][click[1]] == 'M')
            board[click[0]][click[1]] = 'X';
        else
        {
            bfs(board, click[0], click[1]);
        }
        return board;
    }

    char conv2D(vector<vector<char>> &board, int r, int c)
    {
        int sum = 0;
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j)
                if ((0 <= (r + i)) && ((r + i) < board.size()) && (0 <= (c + j)) && ((c + j) < board[0].size()))
                    sum += (board[r + i][c + j] == 'M') ? 1 : 0;
        return sum ? ('0' + sum) : 'B';
    }

    void bfs(vector<vector<char>> &board, int r, int c)
    {
        if(board[r][c] != 'E')
            return;

        board[r][c] = conv2D(board, r, c);

        if (board[r][c] == 'B')
        {
            for (int i = -1; i <= 1; ++i)
                for (int j = -1; j <= 1; ++j)
                    if ((0 <= (r + i)) && ((r + i) < board.size()) && (0 <= (c + j)) && ((c + j) < board[0].size()))
                        bfs(board, r + i, c + j);
        }
    }
};

int main()
{
    vector<vector<char>> board{{'E', 'E', 'E', 'E', 'E'},
                               {'E', 'E', 'M', 'E', 'E'},
                               {'E', 'E', 'E', 'E', 'E'},
                               {'E', 'E', 'E', 'E', 'E'}};
    vector<int> click{3, 0};
    vector<vector<char>> ans{{'B', '1', 'E', '1', 'B'},
                             {'B', '1', 'M', '1', 'B'},
                             {'B', '1', '1', '1', 'B'},
                             {'B', 'B', 'B', 'B', 'B'}};
    Solution sol;
    auto res = sol.updateBoard(board, click);
    cout << ((ans == res) ? "Sucess" : "Fail") << endl;
    for( auto row: res)
    {
        for (auto item : row)
            cout << item << " ";
        cout << endl;
    }
}