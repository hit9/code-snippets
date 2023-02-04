// 从二维矩阵中查找一个数字
// https://writings.sh/post/algorithm-search-sorted-2d-matrix

#include <assert.h>

// Result 是查找的结果
struct Result {
    int row;
    int col;
};

// MatrixSearch 从给定的行数为 row ，列数为 col 的矩阵 matrix 中查找 target
// 如果存在，则返回 Result ，否则，返回 Result{-1,-1} 。
// 其中，matrix 的行和列都是严格递增的
// 比如 1 4 7
//      2 5 8
//      3 6 9
struct Result MatrixSearch(int rows, int cols, int matrix[rows][cols],
                           int target) {
    struct Result not_found = {-1, -1};
    if (rows <= 0 || cols <= 0) return not_found;

    // 从右上角开始探索
    int row = 0;
    int col = cols - 1;

    while (row < rows && col >= 0) {
        if (matrix[row][col] < target) {
            row++;
        } else if (matrix[row][col] > target) {
            col--;
        } else {
            return (struct Result){row, col};
        }
    }
    return not_found;
}

int main(void) {
    int matrix[3][4] = {
        {1, 4, 7, 10},
        {2, 5, 8, 11},
        {3, 6, 9, 12},
    };

    struct Result result = MatrixSearch(3, 4, matrix, 9);
    assert(result.row == 2 && result.col == 2);
}
