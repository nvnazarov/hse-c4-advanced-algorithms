#include <ios>
#include <iostream>
#include <vector>

const int MAX_N = 1e3;
const int MAX_M = 1e3;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  if (n < 1 || n > MAX_N) {
    return 1;
  }
  std::vector<int> a(n);
  for (int &e : a) {
    std::cin >> e;
  }

  int m;
  std::cin >> m;
  if (m < 1 || m > MAX_M) {
    return 1;
  }
  std::vector<int> b(m);
  for (int &e : b) {
    std::cin >> e;
  }

  int a_size = a.size();
  int b_size = b.size();
  std::vector<std::vector<int>> dp(a_size + 1, std::vector<int>(b_size + 1, 0));
  for (int ai = 1; ai <= a_size; ++ai) {
    for (int bi = 1; bi <= b_size; ++bi) {
      if (a[ai - 1] == b[bi - 1]) {
        dp[ai][bi] = dp[ai - 1][bi - 1] + 1;
      } else {
        dp[ai][bi] = std::max(dp[ai - 1][bi], dp[ai][bi - 1]);
      }
    }
  }

  std::cout << dp[a_size][b_size];
  return 0;
}