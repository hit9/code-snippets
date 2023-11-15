// https://leetcode.cn/problems/spiral-matrix-ii/description/

#include <iostream>
#include <vector>
using namespace std;

// 顺时针: (direction +1) % 4

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

class Solution {
   public:
    void next(const vector<vector<int>> &d, int &direction, int &i, int &j) {
        int n = d.size();
        switch (direction) {
            case RIGHT:
                if (j >= n - 1 || d[i][j + 1] > 0)
                    return next(d, direction = DOWN, i, j);
                j++;
                break;
            case DOWN:
                if (i >= n - 1 || d[i + 1][j] > 0)
                    return next(d, direction = LEFT, i, j);
                i++;
                break;
            case LEFT:
                if (j == 0 || d[i][j - 1] > 0)
                    return next(d, direction = UP, i, j);
                j--;
                break;
            case UP:
                if (i == 0 || d[i - 1][j] > 0)
                    return next(d, direction = RIGHT, i, j);
                i--;
                break;
        }
    }

    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> d(n, vector<int>(n, 0));
        int k = 1;
        int direction = RIGHT;
        int i = 0, j = 0;
        while (k < n * n) {
            d[i][j] = k++;
            next(d, direction, i, j);
        }
        // 注意: 最后一个元素无法填写，因为 next 函数在最后一个元素上无路可走
        // 最后补上即可
        d[i][j] = n * n;
        return d;
    }
};

int main(void) {
    Solution solution;
    auto d = solution.generateMatrix(8);
    for (auto i = 0; i < d.size(); i++) {
        for (auto j = 0; j < d[i].size(); j++) {
            cout << d[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << endl;
    return 0;
}
