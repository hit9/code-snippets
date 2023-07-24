// 一个简单的 Map 实现
// 1. 无排序
// 2. 采用哈希开放寻址
// 3. 没实现扩容
// 编译选项 -std=c++20

#include <cstddef>
#include <functional>

// K 是 Key 的类型
// V 是 Value 的类型
// hash 是哈希函数
template <typename K, typename V, std::size_t N, auto hash = std::hash<K>{}>
class Map {
   private:
    // 节点
    class Node {
       public:
        K k;
        V v;
        bool used;
        Node() : k(K{}), v(V{}), used(false){};
    };

    // 最大容量
    static const std::size_t cap = N * 1.2;
    // 底层 buffer
    Node b[cap];
    // 元素计数
    size_t n = 0;

   public:
    Map() = default;

    // 开放寻址法返回位置
    std::size_t Hash(K k, size_t i) const { return (hash(k) + i) % cap; }

    // 大小
    size_t Size() const { return n; };
    size_t Cap() const { return cap; };

    // 添加或更新键 k 的值为 v
    // 如果 m 不足以容纳，返回 false
    bool Set(K k, V v) {
        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i);
            auto& node = b[p];
            // 添加或更新
            // 开放寻址: 冲突时即 node.used 且 node.k != k,
            // 则会继续向前 Hash 找位置
            if (!node.used || node.k == k) {
                node.k = k;
                node.v = v;
                node.used = true;
                n++;
                return true;
            }
        }
        return false;
    };

    // 获取键 k 的值，如果不存在则报错
    V Get(K k) const {
        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i);
            auto& node = b[p];
            if (node.used && node.k == k) return node.v;
        }
        throw std::runtime_error("key not found");
    };

    // 测试键 k 是否在表 m 中
    bool Has(K k) const {
        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i);
            auto& node = b[p];
            if (node.used && node.k == k) return true;
        }
        return false;
    };

    // 弹出键 k，返回它的值。如果不存在则报错
    V Pop(K k) {
        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i);
            auto& node = b[p];
            if (node.used && node.k == k) {
                node.used = false;
                n--;
                return node.v;
            }
        }
        throw std::runtime_error("key not found");
    };
};
