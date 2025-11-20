#include <iostream>
#include <string>
#include <vector>

const int MAX_LENGTH = 1000;

int main() {
  std::string a;
  std::string b;
  std::cin >> a >> b;
  int a_size = a.size();
  int b_size = b.size();
  if (a_size > MAX_LENGTH || b_size > MAX_LENGTH) {
    return 1;
  }

  std::vector<std::vector<int>> dp(a_size + 1, std::vector<int>(b_size + 1, 0));
  for (int ai = 0; ai < a_size; ++ai) {
    dp[ai][0] = ai;
  }
  for (int bi = 0; bi < b_size; ++bi) {
    dp[0][bi] = bi;
  }

  for (int ai = 1; ai <= a_size; ++ai) {
    for (int bi = 1; bi <= b_size; ++bi) {
      // Addition.
      dp[ai][bi] = std::min(dp[ai - 1][bi], dp[ai][bi - 1]) + 1;

      // Replacement.
      if (a[ai - 1] == b[bi - 1]) {
        dp[ai][bi] = std::min(dp[ai][bi], dp[ai - 1][bi - 1]);
      } else {
        dp[ai][bi] = std::min(dp[ai][bi], 1 + dp[ai - 1][bi - 1]);
      }

      // Permutation.
      if (ai >= 2 && bi >= 2 && a[ai - 1] == b[bi - 2] &&
          a[ai - 2] == b[bi - 1]) {
        dp[ai][bi] = std::min(dp[ai][bi], 1 + dp[ai - 2][bi - 2]);
      }
    }
  }

  std::cout << dp[a_size][b_size];
  return 0;
}