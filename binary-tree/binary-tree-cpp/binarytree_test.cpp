#include "binarytree.hpp"

#include <catch2/catch_test_macros.hpp>
#include <vector>

using namespace std;
using namespace binary_tree;

TEST_CASE("ToArray", "[ToArray #1]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    REQUIRE(root->val == 0);
    REQUIRE(root->left->val == 1);
    REQUIRE(root->right->val == 2);
}

TEST_CASE("ToArray", "[ToArray and FromArray #2]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    auto a1 = ToArray(root);
    REQUIRE(a == a1);
}

TEST_CASE("ToArray", "[ToArray and FromArray #3]") {
    vector<int> a{2, 3, -1, 4, -1, 5, -1, 6};
    auto root = FromArray(a);
    auto a1 = ToArray(root);
    REQUIRE(a == a1);
}

TEST_CASE("ToArray", "[ToArray and FromArray #4]") {
    vector<int> a{2, -1, 3, -1, 4, -1, 5, -1, 7};
    auto root = FromArray(a);
    auto a1 = ToArray(root);
    REQUIRE(a == a1);
}

TEST_CASE("BFS", "[BFS #1]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    auto ans = BFS(root);
    vector<int> expect{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(ans == expect);
}

TEST_CASE("PreOrder", "[PreOrder Recursive]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    vector<int> ans;
    PreOrder(root, ans);
    vector<int> expect{0, 1, 3, 7, 8, 4, 9, 2, 5, 6};
    REQUIRE(ans == expect);
}

TEST_CASE("PreOrder", "[PreOrder Non Recursive]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    auto ans = PreOrder(root);
    vector<int> expect{0, 1, 3, 7, 8, 4, 9, 2, 5, 6};
    REQUIRE(ans == expect);
}

TEST_CASE("InOrder", "[InOrder Recursive]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    vector<int> ans;
    InOrder(root, ans);
    vector<int> expect{7, 3, 8, 1, 9, 4, 0, 5, 2, 6};
    REQUIRE(ans == expect);
}

TEST_CASE("InOrder", "[InOrder Non Recursive]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    auto ans = InOrder(root);
    vector<int> expect{7, 3, 8, 1, 9, 4, 0, 5, 2, 6};
    REQUIRE(ans == expect);
}

TEST_CASE("PostOrder", "[PostOrder Recursive]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    vector<int> ans;
    PostOrder(root, ans);
    vector<int> expect{7, 8, 3, 9, 4, 1, 5, 6, 2, 0};
    REQUIRE(ans == expect);
}

TEST_CASE("PostOrder", "[PostOrder Non Recursive]") {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto root = FromArray(a);
    auto ans = PostOrder(root);
    vector<int> expect{7, 8, 3, 9, 4, 1, 5, 6, 2, 0};
    REQUIRE(ans == expect);
}

TEST_CASE("LevelOrder", "[LevelOrder]") {
    vector<int> a{2, 3, 4, -1, 5, 6, 7};
    auto root = FromArray(a);
    auto ans = LevelOrder(root);
    vector<vector<int>> expect{{2}, {3,4}, {5,6,7}};
    REQUIRE(ans == expect);
}


