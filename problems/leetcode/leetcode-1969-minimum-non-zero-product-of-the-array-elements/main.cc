using ll =  long long;
const ll M = 1e9 + 7;
class Solution {
   public:
    // 计算 (a^b)%mod
    ll fastpow(ll x, ll n, ll mod) {
        ll a = x % mod;
        ll b = 1;
        while (n) {
            if (n & 1) {
                b = b * a % mod;
                n--;
            } else {
                n >>= 1;
                a = a * a % mod;
            }
        }
        return b % mod;
    }
    int minNonZeroProduct(int p) {
        if (p == 1) return 1;
        ll k = (1ULL << (p - 1)) - 1;
        ll x = (1ULL << p) - 1;
        ll z = fastpow(2 * k, k, M);
        return (x % M * z) % M;
    }
};
