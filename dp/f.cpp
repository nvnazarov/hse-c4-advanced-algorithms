#include <algorithm>
#include <climits>
#include <iostream>

const int MAX_N = 100;
const int MAX_COORD = 1e4;

int main() {
  int n;
  std::cin >> n;
  if (n < 2 || n > MAX_N) {
    return 1;
  }

  int coords[MAX_N];
  for (int i = 0; i < n; ++i) {
    int &coord = coords[i];
    std::cin >> coord;
    if (coord < 0 || coord > MAX_COORD) {
      return 1;
    }
  }
  std::sort(std::begin(coords), std::begin(coords) + n);

  int dp[MAX_N + 1]{};
  dp[2] = coords[1] - coords[0];
  for (int i = 3; i <= n; ++i) { // i is the number of nails included.
    dp[i] = coords[i - 1] - coords[0];

    // j is the index of the nail the last nail is connected with.
    for (int j = 2; j < i - 1; ++j) {
      dp[i] = std::min(dp[i], dp[j] + coords[i - 1] - coords[j]);
    }
  }

  std::cout << dp[n];
}