// 一个简单的堆上 Map 实现
// 1. 采用哈希开放寻址
// 2. 带自动扩容 (容量倍增)
// 编译选项 -std=c++20

#include <cstddef>
#include <functional>

// K 是 Key 的类型
// V 是 Value 的类型
// hash 是哈希函数
// load_factor 是负载因子
template <typename K, typename V, auto hash = std::hash<K>{}>
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
    std::size_t cap = 8;

    // 底层 buffer
    Node* b = nullptr;

    // 元素计数
    size_t n = 0;

    // 负载因子
    static constexpr double load_factor = 0.75;

   public:
    // 构造空 Map
    Map() { b = new Node[cap]{}; };

    // 开放寻址法返回位置
    std::size_t Hash(K k, size_t i, size_t cap) const {
        return (hash(k) + i) % cap;
    }

    // 大小
    size_t Size() const { return n; };
    size_t Cap() const { return cap; };

    // 扩展, 按两倍进行
    void Resize() {
        auto new_cap = 2 * cap;
        auto new_b = new Node[new_cap]{};

        // 拷贝、重新 hash
        for (auto i = 0; i < cap; i++) {
            auto& node = b[i];
            if (node.used) {
                for (auto j = 0; j < new_cap; j++) {
                    auto p = Hash(node.k, j, new_cap);
                    auto& new_node = new_b[p];
                    if (!new_node.used) {
                        new_node.k = node.k;
                        new_node.v = node.v;
                        new_node.used = true;
                        break;
                    }
                }
            }
        }

        cap = new_cap;
        b = new_b;
    }

    // 添加或更新键 k 的值为 v
    // 如果 m 不足以容纳，返回 false
    bool Set(K k, V v) {
        if (cap * load_factor < n) Resize();

        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i, cap);
            auto& node = b[p];
            // 添加或更新
            // 开放寻址: 冲突时即 node.used 且 node.k != k,
            // 则会继续向前 Hash 找位置
            if (!node.used || node.k == k) {
                node.k = k;
                node.v = v;
                if (!node.used) {
                    node.used = true;
                    n++;
                }
                return true;
            }
        }
        return false;
    };

    // 获取键 k 的值，如果不存在则报错
    V Get(K k) const {
        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i, cap);
            auto& node = b[p];
            if (node.used && node.k == k) return node.v;
        }
        throw std::runtime_error("key not found");
    };

    // 测试键 k 是否在表 m 中
    bool Has(K k) const {
        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i, cap);
            auto& node = b[p];
            if (node.used && node.k == k) return true;
        }
        return false;
    };

    // 弹出键 k，返回它的值。如果不存在则报错
    V Pop(K k) {
        for (auto i = 0; i < cap; i++) {
            auto p = Hash(k, i, cap);
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
