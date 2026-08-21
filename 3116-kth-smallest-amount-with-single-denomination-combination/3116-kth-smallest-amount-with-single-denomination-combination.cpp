class Solution {
public:
    long long findKthSmallest(vector<int>& coins, int k) {
        long long left = 1, right = 1LL * *max_element(coins.begin(), coins.end()) * k;
        long long ans = -1;

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (countAmounts(coins, mid) >= k) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

private:
    long long countAmounts(vector<int>& coins, long long x) {
        int n = coins.size();
        long long total = 0;

        // Inclusion-Exclusion principle
        for (int mask = 1; mask < (1 << n); mask++) {
            long long lcm = 1;
            int bits = __builtin_popcount(mask);
            bool overflow = false;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    long long g = gcd(lcm, (long long)coins[i]);
                    if (lcm > x / (coins[i] / g)) { // prevent overflow
                        overflow = true;
                        break;
                    }
                    lcm = lcm / g * coins[i];
                }
            }

            if (!overflow) {
                long long cnt = x / lcm;
                if (bits % 2 == 1) total += cnt;
                else total -= cnt;
            }
        }
        return total;
    }

    long long gcd(long long a, long long b) {
        return b == 0 ? a : gcd(b, a % b);
    }
};
