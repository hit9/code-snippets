#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(), piles.end());
        int sum = 0;
        for (int j = piles.size() - 2, i = 0; j > i; j -= 2, i++)
            sum += piles[j];
        return sum;
    }
};
