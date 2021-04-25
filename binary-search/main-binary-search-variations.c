// 二分查找的变种问题

#include <assert.h>

// 一个数组前面是 0 后面是 1
// 找到第一个 1 的位置
int First1(int n, int a[n]) {
    if (n <= 0) return -1;
    int l = 0;       // [, l) 是已知的 0 的区间
    int r = n - 1;   // [r,) 是已知的 1 的区间
    while (l < r) {  // 当 l==r 时，所有未知变已知
        int m = l + (r - l) / 2;
        if (a[m] == 0) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    return r;
}

// 找出升序数组中元素的左边界
int BinarySearchStart(int n, int a[n], int t) {
    if (n <= 0) return -1;
    int l = 0;      // ,l) 是已知的 < t 的区间
    int r = n - 1;  // [r, 是已知的 >= t 的区间
    while (l < r) {
        int m = l + (r - l) / 2;  // 左边更激进, m 向左靠
        if (a[m] < t) {
            l = m + 1;
        } else {
            r = m;
        }
    }
    if (a[l] == t) return l;  // 如果遇到
    return -1;
}

// 找出升序数组中元素右边界
int BinarySearchEnd(int n, int a[n], int t) {
    if (n <= 0) return -1;
    int l = 0;      // ,l] 是已知的 <= t 的区间
    int r = n - 1;  // (r, 是已知的 > t 的区间
    while (l < r) {
        int m = r - (r - l) / 2;  // 右边更激进, m 向右靠
        if (a[m] > t) {
            r = m - 1;
        } else {
            l = m;
        }
    }
    if (a[r] == t) return r;  // 如果遇到
    return -1;
}

// 升序数组中元素可能重复，找出一个元素的左右边界
// 结果写入 start 和 end;
void BinarySearchRange(int n, int a[n], int t, int *start, int *end) {
    *start = BinarySearchStart(n, a, t);
    *end = BinarySearchEnd(n, a, t);
}

// 升序数组中元素可能重复，找出一个元素的左右边界（第二种方法）
// 结果写入 start 和 end;
void BinarySearchRange2(int n, int a[n], int t, int *start, int *end) {
    if (n <= 0) return;
    int l = 0;      // ,l) 是已知的 < t 的区间
    int r = n - 1;  // (r, 是已知的 > t 的区间
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] < t) {
            l = m + 1;
        } else if (a[m] > t) {
            r = m - 1;
        } else {  // == t
            if (a[r] > t)
                r--;
            else if (a[l] < t)
                l++;
            else  // 左右都t，找到边界
                break;
        }
    }
    *start = l;
    *end = r;
}

// 统计一个数字在有序数组中出现的次数
// 思路1)找出其左右边界
// 思路2)找出t和t-1的右边界
int BinarySearchCount(int n, int a[n], int t) {
    if (n <= 0) return 0;
    return BinarySearchEnd(n, a, t) - BinarySearchEnd(n, a, t - 1);
}

// 旋转数组中查找最小值的位置（可能存在重复元素）
// https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/
int BinarySearchRotatedPeak(int n, int a[n]) {
    if (n <= 0) return -1;
    int l = 0;
    int r = n - 1;
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] == a[r])  //  例如 [2,2,2,0,2] 最小值一定在 r 左边
            r--;
        else if (a[m] < a[r])  // 例如 [2,2,1,2,2] 最小值一定不在区间 (m,
            r = m;
        else if (a[m] > a[r])  // 例如 [2,3,4,1,2] 最小值一定不在区间 ,m]
            l = m + 1;
    }
    return a[l];
}

////////
// 测试
////////

void TestFirst1() {
    int a[] = {0, 0, 0, 0, 1, 1, 1};
    int n = 7;
    assert(First1(n, a) == 4);
}

void TestBinarySearchStart() {
    int a[] = {0, 1, 2, 3, 3, 3, 5};
    int n = 7;
    assert(BinarySearchStart(n, a, 3) == 3);
}

void TestBinarySearchEnd() {
    int a[] = {0, 1, 2, 3, 3, 3, 5};
    int n = 7;
    assert(BinarySearchEnd(n, a, 3) == 5);
}

void TestBinarySearchRange() {
    int a[] = {0, 1, 2, 3, 3, 3, 5};
    int n = 7;
    int t = 3;
    int start = 0;
    int end = 0;
    BinarySearchRange(n, a, t, &start, &end);
    assert(start == 3 && end == 5);
}

void TestBinarySearchRange2() {
    int a[] = {0, 1, 2, 3, 3, 3, 5};
    int n = 7;
    int t = 3;
    int start = 0;
    int end = 0;
    BinarySearchRange2(n, a, t, &start, &end);
    assert(start == 3 && end == 5);
}

void TestBinarySearchCount() {
    int a[] = {0, 1, 2, 3, 3, 3, 5};
    int n = 7;
    int t = 3;
    assert(BinarySearchCount(n, a, t) == 3);
}

void TestBinarySearchRotatedPeak() {
    int a[] = {4, 5, 6, 6, 6, 7, 7, 7, 1, 1, 2, 3, 3, 3, 3};
    int n = 15;
    assert(BinarySearchRotatedPeak(n, a) == 1);
}

int main(void) {
    TestFirst1();
    TestBinarySearchStart();
    TestBinarySearchEnd();
    TestBinarySearchRange();
    TestBinarySearchRange2();
    TestBinarySearchCount();
    TestBinarySearchRotatedPeak();
    return 0;
}
