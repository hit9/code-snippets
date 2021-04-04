"""
二叉树 Python 版
"""


class TreeNode:
    """二叉树，值为整型"""

    def __init__(self, v):
        self.v = v
        self.left = None
        self.right = None


########
# 遍历
########


def bt_bfs(root):
    """广度优先遍历"""
    if not root:
        return
    q = [root]
    a = []  # 数值数组
    while len(q) > 0:
        node = q.pop(0)
        if not node:
            continue
        a.append(node.v)
        q.append(node.left)
        q.append(node.right)
    return a


def bt_preorder_recur(root, a):
    """bt_preorder 的辅助函数"""
    if not root:
        return
    a.append(root.v)
    bt_preorder_recur(root.left, a)
    bt_preorder_recur(root.right, a)


def bt_preorder(root):
    """前序遍历（递归）"""
    a = []
    bt_preorder_recur(root, a)
    return a


def bt_inorder_recur(root, a):
    """bt_inorder_recur 的辅助函数"""
    if not root:
        return
    bt_inorder_recur(root.left, a)
    a.append(root.v)
    bt_inorder_recur(root.right, a)


def bt_inorder(root):
    """中序遍历（递归）"""
    a = []
    bt_inorder_recur(root, a)
    return a


def bt_postorder_recur(root, a):
    """bt_postorder 的辅助函数"""
    if not root:
        return
    bt_postorder_recur(root.left, a)
    bt_postorder_recur(root.right, a)
    a.append(root.v)


def bt_postorder(root):
    """后序遍历（递归）"""
    a = []
    bt_postorder_recur(root, a)
    return a


def bt_preorder_ii(root):
    """前序遍历（非递归）"""
    if not root:
        return
    s = [(root, False)]  # 栈 (节点，是否访问过)
    a = []  # 数值结果集

    while len(s) > 0:
        node, visited = s.pop()
        if not node:
            continue
        if not visited:
            s.append((node.right, False))
            s.append((node.left, False))
            s.append((node, True))
        else:
            a.append(node.v)
    return a


def bt_inorder_ii(root):
    """中序遍历（非递归）"""
    if not root:
        return
    s = [(root, False)]  # 栈 (节点，是否访问过)
    a = []  # 数值结果集

    while len(s) > 0:
        node, visited = s.pop()
        if not node:
            continue
        if not visited:
            s.append((node.right, False))
            s.append((node, True))
            s.append((node.left, False))
        else:
            a.append(node.v)
    return a


def bt_postorder_ii(root):
    """后序遍历（非递归）"""
    if not root:
        return
    s = [(root, False)]  # 栈 (节点，是否访问过)
    a = []  # 数值结果集

    while len(s) > 0:
        node, visited = s.pop()
        if not node:
            continue
        if not visited:
            s.append((node, True))
            s.append((node.right, False))
            s.append((node.left, False))
        else:
            a.append(node.v)
    return a


########
# 简单问题
########


def bt_compare(a, b):
    """比较两个二叉树是否完全相同"""
    if not a and not b:
        return True
    if a and not b:
        return False
    if not a and b:
        return False
    return a.v == b.v and bt_compare(a.left, b.left) and bt_compare(a.right, b.right)


def bt_count(root):
    """返回二叉树的节点数目"""
    if not root:
        return 0
    return 1 + bt_count(root.left) + bt_count(root.right)


def bt_max_depth(root):
    """返回二叉树的最大深度"""
    if not root:
        return 0
    d1 = bt_max_depth(root.left)
    d2 = bt_max_depth(root.right)
    return max(d1, d2) + 1


def bt_min_depth(root):
    """返回二叉树的最小深度"""
    if not root:
        return 0
    d1 = bt_min_depth(root.left)
    d2 = bt_min_depth(root.right)
    if not root.left:
        return d2 + 1
    if not root.right:
        return d1 + 1
    return min(d1, d2) + 1


def bt_is_two_bt_symmetric(a, b):
    """判断两个二叉树是否镜像相等

       2         2
     3   4     4   3
    5 6 7 8   8 7 6 5
    => True
    """
    if not a and not b:
        return True
    if not a and b:
        return False
    if not b and a:
        return False
    return (
        a.v == b.v
        and bt_is_two_bt_symmetric(a.left, b.right)
        and bt_is_two_bt_symmetric(a.right, b.left)
    )


def bt_is_symmetric(root):
    """判断二叉树是否镜像
        1
      2   2
    3  4 4  3
    => True
    """
    if not root:
        return True
    return bt_is_two_bt_symmetric(root.left, root.right)


########
# 序列化
########


def bt_from_array(a):
    """
    从数组构建二叉树
    例如

    [2,3,4,-1,5,6,-1,-1,-1,7]
    =>
            2
          3   4
            5   6
                  7

    [2,-1,3,-1,4]
    =>
            2
              3
                4
    """
    if not a:
        return None
    if a[0] == -1:
        return None

    root = TreeNode(a[0])
    q = [root]  # 存放上一层节点
    i = 1  # 迭代数组 a

    while len(q) > 0:
        node = q.pop(0)

        if not node:
            continue

        if i < len(a):  # 当前节点的左孩子
            v = a[i]
            i += 1
            if v != -1:
                node.left = TreeNode(v)

        if i < len(a):  # 当前节点的右孩子
            v = a[i]
            i += 1
            if v != -1:
                node.right = TreeNode(v)

        # 将左右孩子作为下一次迭代的上一层节点
        if node.left:
            q.append(node.left)
        if node.right:
            q.append(node.right)
    return root


def bt_to_array(root):
    """
    二叉树转为数组，即 bt_from_array 的逆函数
    """
    if not root:
        return []
    q = [root]  # 记录上一层节点
    a = []  # 数值数组
    ec = 0  # 记录自上一非空节点依赖的空节点数量
    while len(q) > 0:
        node = q.pop(0)
        if not node:
            ec += 1
            continue
        # 刷之前的 -1
        while ec > 0:
            ec -= 1
            a.append(-1)
        # 记录当前非空值
        a.append(node.v)
        # 当前孩子作为下一次迭代的上一层
        q.append(node.left)
        q.append(node.right)
    return a
