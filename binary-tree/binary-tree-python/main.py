from tree import *


def test_bfs():
    root = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    a = bt_bfs(root)
    assert a == [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]


def test_bt_preorder():
    root = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    a = bt_preorder(root)
    assert a == [0, 1, 3, 7, 8, 4, 9, 2, 5, 6]


def test_bt_inorder():
    root = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    a = bt_inorder(root)
    assert a == [7, 3, 8, 1, 9, 4, 0, 5, 2, 6]


def test_bt_postorder():
    root = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    a = bt_postorder(root)
    assert a == [7, 8, 3, 9, 4, 1, 5, 6, 2, 0]


def test_bt_preorder_ii():
    root = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    a = bt_preorder_ii(root)
    assert a == [0, 1, 3, 7, 8, 4, 9, 2, 5, 6]


def test_bt_inorder_ii():
    root = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    a = bt_inorder_ii(root)
    assert a == [7, 3, 8, 1, 9, 4, 0, 5, 2, 6]


def test_bt_postorder_ii():
    root = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    a = bt_postorder_ii(root)
    assert a == [7, 8, 3, 9, 4, 1, 5, 6, 2, 0]


def test_bt_level_order():
    root = bt_from_array([2, 3, 4, -1, 5, 6, 7])
    a = bt_level_order(root)
    assert a == [[2], [3, 4], [5, 6, 7]]

    root1 = bt_from_array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    b = bt_level_order(root1)
    assert b == [[0], [1, 2], [3, 4, 5, 6], [7, 8, 9]]


def test_bt_invert():
    a = bt_from_array([4, 2, 7, 1, 3, 6, 9])
    b = bt_from_array([4, 7, 2, 9, 6, 3, 1])
    assert bt_compare(b, bt_invert(a))
    c = [4, 2, 7, 1, 3, 6, 9]
    a1 = bt_from_array(c)
    assert bt_to_array(bt_invert(bt_invert(a1))) == c


def test_bst_find():
    a = bt_from_array([5, 3, 6, 2, 4, -1, -1, 1])
    b = bst_find(a, 3)
    assert b.v == 3


def test_bst_kth1():
    a = bt_from_array([5, 3, 6, 2, 4, -1, -1, 1])
    assert bst_kth1(a, 3) == 3


def test_bst_kth2():
    a = bt_from_array([5, 3, 6, 2, 4, -1, -1, 1])
    assert bst_kth2(a, 3) == 3


def test_bt_is_substructure():
    a = bt_from_array([4, 2, 3, 4, 5, 6, 7, 8, 9])
    b = bt_from_array([4, 8, 9])
    assert bt_is_substructure(a, b)


def test_from_to_array():
    a1 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    r1 = bt_from_array(a1)
    b1 = bt_to_array(r1)
    r11 = bt_from_array(b1)
    assert b1 == a1
    assert bt_compare(r1, r11)

    a2 = [2, 3, -1, 4, -1, 5, -1, 6]
    r2 = bt_from_array(a2)
    b2 = bt_to_array(r2)
    r21 = bt_from_array(b2)
    assert b2 == a2
    assert bt_compare(r2, r21)

    a3 = [2, -1, 3, -1, 4, -1, 5, -1, 7]
    r3 = bt_from_array(a3)
    b3 = bt_to_array(r3)
    r31 = bt_from_array(b3)
    assert b3 == a3
    assert bt_compare(r3, r31)


def test_bt_count():
    a = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    root = bt_from_array(a)
    assert bt_count(root) == len(a)


def test_bt_max_depth():
    a = [0, 1, 2, -1, -1, -1, 3, -1, 4]
    root = bt_from_array(a)
    assert bt_max_depth(root) == 4


def test_bt_min_depth():
    a = [0, 1, 2, -1, -1, -1, 3, -1, 4]
    root = bt_from_array(a)
    assert bt_min_depth(root) == 2


def test_bt_is_symmetric():
    a = [1, 2, 2, 3, 4, 4, 3]
    assert bt_is_symmetric(bt_from_array(a))
    b = [1, 2, 2, -1, 3, -1, 3]
    assert not bt_is_symmetric(bt_from_array(b))


def test_is_balanced():
    assert bt_is_balanced(bt_from_array([3, 9, 20, -1, -1, 15, 7]))
    assert bt_is_balanced(not bt_from_array([1, 2, 2, 3, 3, -1, -1, 4, 4]))


def test_is_bst1():
    assert bt_is_bst1(bt_from_array([5, 3, 7, 2, 4, 6, 8]))
    assert bt_is_bst1(bt_from_array([2, 1, 3]))
    assert not bt_is_bst1(bt_from_array([5, 1, 4, -1, -1, 3, 6]))


def test_is_bst2():
    assert bt_is_bst2(bt_from_array([5, 3, 7, 2, 4, 6, 8]))
    assert bt_is_bst2(bt_from_array([2, 1, 3]))
    assert not bt_is_bst2(bt_from_array([5, 1, 4, -1, -1, 3, 6]))


def test_lowest_common_ancestor():
    a = bt_from_array([3, 5, 2, 1, 6, 0, 8, -1, -1, 7, 4])
    p = bt_find(a, 7)
    q = bt_find(a, 8)
    r = bt_lowest_common_ancestor(a, p, q)
    assert r and r.v == 3


def test_bst_lowest_common_ancestor():
    a = bt_from_array([6, 2, 8, 0, 4, 7, 9, -1, -1, 3, 5])
    p = bst_find(a, 2)
    q = bst_find(a, 8)
    b = bst_lowest_common_ancestor(a, p, q)
    assert b and b.v == 6


def test_bt_flatten():
    a = bt_from_array([1, 2, 5, 3, 4, -1, 6])
    b = bt_from_array([1, -1, 2, -1, 3, -1, 4, -1, 5, -1, 6])
    assert bt_compare(bt_flatten(a), b)


def main():
    test_bfs()
    test_bt_preorder()
    test_bt_inorder()
    test_bt_postorder()
    test_bt_preorder_ii()
    test_bt_inorder_ii()
    test_bt_postorder_ii()
    test_bt_level_order()
    test_from_to_array()
    test_bt_count()
    test_bt_max_depth()
    test_bt_min_depth()
    test_bt_is_symmetric()
    test_is_balanced()
    test_is_bst1()
    test_is_bst2()
    test_bt_invert()
    test_bst_find()
    test_bst_kth1()
    test_bst_kth2()
    test_bt_is_substructure()
    test_lowest_common_ancestor()
    test_bst_lowest_common_ancestor()
    test_bt_flatten()


if __name__ == "__main__":
    main()
