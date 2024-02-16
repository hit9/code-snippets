class Solution {
public:
    int iceBreakingGame(int n, int k) {
        int p = 0;
        for (int i = 2; i <= n; i++) {
            p = (p + k) % i;
        }
        return p;
      }
};
