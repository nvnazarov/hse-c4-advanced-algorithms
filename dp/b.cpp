#include <ios>
#include <iostream>
#include <vector>

const int MAX_N = 3000;
const int MAX_M = 3000;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int n, m;
  std::cin >> n >> m;
  if (n < 1 || m < 1 || n > MAX_N || m > MAX_M) {
    return 1;
  }

  std::vector<std::vector<int>> array(n, std::vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int &a = array[i][j];
      std::cin >> a;
      if (a != 0 && a != 1) {
        return 1;
      }
    }
  }

  // dp[i][j] = max length of a side of a square whose bottom-right cell
  // is at (i,j) (i is in 1..n, j is in 1..m).
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (array[i - 1][j - 1] == 1) {
        if (int a = dp[i - 1][j], b = dp[i][j - 1]; a != b) {
          dp[i][j] = 1 + std::min(a, b);
        } else if (array[i - a - 1][j - a - 1] == 1) {
          dp[i][j] = 1 + a;
        } else {
          dp[i][j] = std::max(1, a);
        }
      }
    }
  }

  int x = 0;
  int y = 0;
  int length = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (int dp_length = dp[i][j]; dp_length > length) {
        length = dp_length;
        x = i - length + 1;
        y = j - length + 1;
      }
    }
  }

  std::cout << length << "\n" << x << " " << y;
  return 0;
}