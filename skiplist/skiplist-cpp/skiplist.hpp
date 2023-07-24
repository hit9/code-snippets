// 跳跃表 C++ 实现
// 介绍: https://writings.sh/post/data-structure-skiplist
// 编译选项: -std=c++20

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

// 最大层数
static const int MAX_LEVEL = 16;

// 跳表
template <typename T, auto Less = std::less<T>{}>
class Skiplist {
   private:
    // 节点结构
    class Node {
       public:
        T v;                                       // 数据
        std::vector<std::shared_ptr<Node>> nexts;  // 前进数组

        // 构造函数
        Node(T v, int level)
            : v(v), nexts(std::vector<std::shared_ptr<Node>>(level, nullptr)){};
    };

    bool Equals(T a, T b) { return !Less(a, b) && !Less(b, a); }

    int n = 0;                             // 节点数目
    int level = 1;                         // 最大层数, 默认是 1
    std::shared_ptr<Node> head = nullptr;  // 头节点

    // 生成一个 1 到 MAX_LEVEL 之间的随机层数
    static int RandLevel() {
        int lv = 1;
        // 以概率 P 递增 level
        // 1/2 的概率 level → 1
        // 1/4 的概率 level → 2
        // 1/8 的概率 level → 3
        while ((std::rand() & 65535) * 1.0 / 65535 < 0.5) lv++;
        return lv < MAX_LEVEL ? lv : MAX_LEVEL;
    };

   public:
    // 新建一个跳跃表
    // head 实际不存储任何数据
    Skiplist() : head(std::make_shared<Node>(T{}, MAX_LEVEL)){};

    // 获取元素个数
    int Size() { return n; }

    // 添加一个元素
    void Put(T v) {
        // 第一步，找到各层插入的位置

        // last[i] 表示第 i 层的插入位置的前驱节点
        std::shared_ptr<Node> last[MAX_LEVEL];
        auto node = head;

        for (int i = level - 1; i >= 0; i--) {
            // 自顶向下, 自左向右的比较大小
            while (node->nexts[i] != nullptr && Less(node->nexts[i]->v, v)) {
                node = node->nexts[i];
            }
            last[i] = node;
        }

        // 第二步 生成新节点和层数
        // 计算新的层数
        int lv = RandLevel();

        if (lv > level) {
            // 新节点的层数比原来的都大
            // 需要补充 last 数组高位，将把 head 指向此节点
            for (int i = level; i < lv; i++) {
                last[i] = head;
            }
            level = lv;
        }

        // 第三步，各层执行插入
        auto new_node = std::make_shared<Node>(v, lv);

        for (int i = 0; i < lv; i++) {
            new_node->nexts[i] = last[i]->nexts[i];
            last[i]->nexts[i] = new_node;
        }

        n++;
    }

    // 返回 v 是否在跳表中
    bool Has(T v) {
        auto node = head;
        for (int i = level; i >= 0; i--) {
            while (node->nexts[i] != nullptr && Less(node->nexts[i]->v, v)) {
                node = node->nexts[i];
            }
        }
        node = node->nexts[0];
        return node != nullptr && Equals(node->v, v);
    };

    // 从跳表中删除 v
    bool Pop(T v) {
        // 第一步 找到各层删除位置的前驱节点
        std::shared_ptr<Node> last[MAX_LEVEL];
        auto node = head;
        for (int i = level - 1; i >= 0; i--) {
            // 自顶向下, 自左向右的比较大小
            while (node->nexts[i] != nullptr && Less(node->nexts[i]->v, v)) {
                node = node->nexts[i];
            }
            last[i] = node;
        }

        // 要删除的节点
        node = node->nexts[0];
        if (node == nullptr || !Equals(node->V, v)) return false;

        // 各层执行删除
        for (int i = level - 1; i >= 0; i--) {
            if (last[i]->nexts[i] == node) last[i]->nexts[i] = node->nexts[i];
        }

        // 第三步，去除删除节点后可能造成的无效层次
        while (level > 1 && head->nexts[level - 1] == nullptr) {
            level--;
        }

        n--;
        return true;
    }

    // 获取头元素
    T Top() {
        if (n == 0) throw std::runtime_error("empty skilist");
        return head->nexts[0]->v;
    }

    // 取出头元素
    T PopFirst() {
        if (n == 0) throw std::runtime_error("empty skilist");
        // 第一个元素
        auto n1 = head->nexts[0];
        // 删除 n1
        for (int i = level - 1; i >= 0; i--) {
            if (head->nexts[i] == n1) {
                head->nexts[i] = n1->nexts[i];
            }
        }
        // 抹除高位无效层次
        while (level > 1 && head->nexts[level - 1] == nullptr) {
            level--;
        }
        return n1->v;
    }

    void Print() {
        if (n == 0) return;

        for (int i = level - 1; i >= 0; i--) {
            auto node = head->nexts[i];
            std::cout << "Level[" << i << "]:";
            while (node != nullptr) {
                std::cout << node->v << " -> ";
                node = node->nexts[i];
            }
            std::cout << "Nil" << std::endl;
        }
    }
};
