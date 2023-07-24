// 编译时 map

#include <cstddef>
#include <functional>

template <typename K, typename V, std::size_t N, auto hash = std::hash<K>{}>
class Map {
   private:
    class Node {
       public:
        K k;
        V v;
        bool used;
        constexpr Node(K k, V v) : k(k), v(v), used(false){};
    };

    static const std::size_t cap = N * 1.2;
    Node b[cap];

    constexpr Map() = default;

    constexpr std::size_t Hash(K k, size_t i, std::size_t n) {
        return (hash(k) + i) % n;
    }

    // 添加或更新键 k 的值为 v
    // 如果 m 不足以容纳，返回 false
    constexpr bool Set(K k, V v) {
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
                return true;
            }
        }
        return false;
    };

    //  获取键 k 的值，如果不存在则报错
    constexpr V Get(K k) const {
        auto i = 0;
        for (; i < cap; i++) {
            auto p = Hash(k, i);
            auto& node = b[p];
            if (node.used && node.k == k) return node.v;
        }
        static_assert(i < cap, "key not found");
    }
};
