"""
二叉树 Python 版
"""

from collections import deque


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
    q = deque([root])
    a = []  # 数值数组
    while len(q) > 0:
        node = q.popleft()
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


def bt_level_order(root):
    """层序遍历

        2
      3   4
       5 6 7
    => [[2], [3,4], [5,6,7]]
    """
    if not root:
        return []
    q = deque([root])
    a = []  # 层序遍历结果
    while len(q) > 0:
        qsize = len(q)  # 上一层的节点个数
        b = []
        while qsize > 0:
            node = q.popleft()
            qsize -= 1
            if not node:
                continue
            b.append(node.v)
            q.append(node.left)
            q.append(node.right)
        if b:
            a.append(b)
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


def bt_is_balanced_helper(root):
    """如果是平衡树，返回树的最大深度
    否则返回 -1"""
    if not root:
        return 0
    d1 = bt_is_balanced_helper(root.left)
    d2 = bt_is_balanced_helper(root.right)
    if d1 == -1 or d2 == -1:
        return -1
    if abs(d1 - d2) > 1:
        return -1
    return max(d1, d2) + 1


def bt_is_balanced(root):
    """判断平衡树
    二叉树中任意节点的左右子树的深度相差不超过1 为平衡树
    """
    return bt_is_balanced_helper(root) != -1


def bt_invert(root):
    """翻转二叉树（这是个有故事的二叉树问题）"""
    if not root:
        return None
    root.left, root.right = bt_invert(root.right), bt_invert(root.left)
    return root


def bt_find(root, v):
    """从二叉树中找到值为 v 的节点"""
    if not root:
        return None
    if root.v == v:
        return root
    left = bt_find(root.left, v)
    right = bt_find(root.right, v)
    if left:
        return left
    if right:
        return right
    return None


def bt_is_substructure(a, b):
    """判断树 b 是否是 a 的子结构

    例如
                4
       a    2       3
          4   5   6   7
         8 9

            4
       b   8 9
       => True

    约定：空树不是任何树的子结构
    """

    def helper(a, b):
        """判断 b 是否是 a 的以根节点开始的子树
        或者说是前缀子树"""
        if not b:
            return True
        if not a or a.v != b.v:
            return False
        return helper(a.left, b.left) and helper(a.right, b.right)

    if not b or not a:
        return False
    # b 是 a 在根节点即匹配的前缀子树，必然是子结构
    # 或者 b 是 a 左子树的子结构
    # 或者 b 是 a 右子树的子结构
    return (
        helper(a, b) or bt_is_substructure(a.left, b) or bt_is_substructure(a.right, b)
    )


def bt_lowest_common_ancestor(root, p, q):
    """返回 p 和 q 在二叉树 root 中的最近公共祖先节点

         3
      5     2
    1  6   0  8
      7 4

    p=7, q=8 => 3
    """
    if not root:
        return None
    if root == q or root == p:
        return root

    # bt_lowest_common_ancestor 函数的作用：
    # 如果 p 和 q 都在树中，则返回其最近的公共祖先节点
    # 如果其中一个在树中，另一个不在，则返回这个节点
    # 如果都不在树中，返回 None
    left = bt_lowest_common_ancestor(root.left, p, q)
    right = bt_lowest_common_ancestor(root.right, p, q)

    if left and right:
        # p 和 q 一个在左子树，一个在右子树
        return root
    elif left and not right:
        # p 和 q 都在左子树
        return left
    elif right and not left:
        # p 和 q 都在右子树
        return right
    else:
        return None


def bt_flatten(root):
    """将二叉树展开为链表，先序顺序

         1                  1
      2     5        =>      2
    3   4     6               3
                               4
                                5
                                 6

    """

    def helper(root):
        """展开给定的二叉树，返回展开后的尾巴节点（非空）
        如果树是空的，才返回空节点
        """
        if not root:
            return None

        if not root.left and not root.right:
            # 左右都空，链表尾巴是 root
            return root
        elif not root.left and root.right:
            # 左空、右不空
            # 右孩子展开链表，返回其尾巴
            return helper(root.right)
        elif root.left and not root.left:
            # 左不空、右空
            # 左孩子展开链表，挂在到右孩子上，返回其尾巴
            tail = helper(root.left)
            root.right = root.left
            root.left = None
            return tail
        else:
            # 左右都不空
            # 左右展开链表
            left_tail = helper(root.left)
            right_tail = helper(root.right)

            # 右孩子链表挂在左孩子链表上
            left_tail.right = root.right
            left_tail.left = None

            # 拼接后的链表挂载到右孩子上
            root.right = root.left
            root.left = None

            # 返回右孩子链表的尾巴
            return right_tail

    helper(root)
    return root


########
# 二叉搜索树
########


def bt_is_bst1_helper(root, upper, lower):
    """bt_is_bst1 的辅助函数"""
    if not root:
        return True
    if root.v >= upper or root.v <= lower:
        return False
    return bt_is_bst1_helper(root.left, root.v, lower) and bt_is_bst1_helper(
        root.right, upper, root.v
    )


def bt_is_bst1(root):
    """判断二叉搜索
    二叉搜索树的特征：
    1. 节点的左子树只包含小于当前节点的数
    2. 节点的右子树只包含大于当前节点的数
    3. 所有左子树和右子树自身必须也是二叉搜索树
    方法一： 递归上下界方法
    """
    return bt_is_bst1_helper(root, (1 << 63) - 1, -1 << 63)


def bt_is_bst2_helper(root, last):
    """bt_is_bst2 的辅助函数，
    last 是一个记录上一次中序遍历的数值的单元素列表"""
    if not root:
        return True
    if not bt_is_bst2_helper(root.left, last):
        # 左子树必须是二叉搜索树
        return False
    if last:
        if root.v <= last[0]:
            return False
        # 更新上一个值
        last[0] = root.v
    else:
        #  初始化 last
        last.append(root.v)
    if not bt_is_bst2_helper(root.right, last):
        # 右子树必须是二叉搜索树
        return False
    return True


def bt_is_bst2(root):
    """方法二：二叉搜索树的中序遍历是有序的"""
    return bt_is_bst2_helper(root, [])


def bst_find(root, v):
    """二叉搜索树的查找"""
    if not root:
        return None
    if root.v == v:
        return root
    elif root.v > v:
        return bst_find(root.left, v)
    elif root.v < v:
        return bst_find(root.right, v)


def bst_kth1_helper(root, a, k):
    """递归收集二叉搜索树的前 k 个元素"""
    if not root:
        return

    if len(a) >= k:  # 终止无效递归
        return

    bst_kth1_helper(root.left, a, k)
    a.append(root.v)
    bst_kth1_helper(root.right, a, k)


def bst_kth1(root, k):
    """找出二叉搜索树的第 k 小的元素
    递归版
    性质：二叉搜索树的中序遍历是有序的"""
    a = []
    bst_kth1_helper(root, a, k)
    return a[k - 1]  # 第 k-1 个元素 而不是 -1


def bst_kth2(root, k):
    """找出二叉搜索树的第 k 小的元素
    非递归版
    性质：二叉搜索树的中序遍历是有序的"""
    s = [(root, 0)]
    while len(s) > 0:
        node, visited = s.pop()
        if not node:
            continue
        if visited == 0:
            s.append((node.right, 0))
            s.append((node, 1))
            s.append((node.left, 0))
        else:
            k -= 1  # 处理此节点
            if k == 0:
                return node.v
    return -1


def bst_lowest_common_ancestor(root, p, q):
    """二叉搜索树的最近公共祖先"""
    if not root:
        return None
    if root.v < p.v and root.v < q.v:
        return bst_lowest_common_ancestor(root.right, p, q)
    if root.v > p.v and root.v > q.v:
        return bst_lowest_common_ancestor(root.left, p, q)
    return root


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
    q = deque([root])  # 存放上一层节点
    i = 1  # 迭代数组 a

    while len(q) > 0:
        node = q.popleft()

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
    q = deque([root])  # 记录上一层节点
    a = []  # 数值数组
    ec = 0  # 记录自上一非空节点依赖的空节点数量
    while len(q) > 0:
        node = q.popleft()
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
