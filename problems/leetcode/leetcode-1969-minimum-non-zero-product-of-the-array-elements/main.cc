using ll = long long;
const ll M = 1e9 + 7;
class Solution {
   public:
    // 计算 (a^b)%mod
    ll fastpow(ll a, ll b, ll mod) {
    ll factor = a % mod;
    ll result = 1;
    ll remain = b;
    while (remain > 0) {
        if (remain & 1) {
            // 奇数
            result = result * factor % mod;
            remain--;
        } else {
            // 偶数
            remain = remain / 2;  // 剩余指数拆半
            factor = factor * factor % mod;
            ;  // 因子自乘翻倍
        }
    }
    return result % mod;
    }
    int minNonZeroProduct(int p) {
        if (p == 1) return 1;
        ll k = (1ULL << (p - 1)) - 1;
        ll x = (1ULL << p) - 1;
        ll z = fastpow(2 * k, k, M);
        return (x % M * z) % M;
    }
};
