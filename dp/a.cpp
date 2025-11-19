#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

const int MAX_N = 1e4;
const int MOD = 1e9 + 9;

std::vector<std::tuple<int, int, int>> get_primes_from_100_to_1000() {
  std::vector<bool> is_prime(1000, true);
  is_prime[0] = false;
  is_prime[1] = false;
  for (int i = 2; i <= 1000; ++i) {
    if (is_prime[i]) {
      for (int j = 2 * i; j <= 1000; j += i) {
        is_prime[j] = false;
      }
    }
  }
  std::vector<std::tuple<int, int, int>> primes;
  for (int i = 100; i <= 1000; ++i) {
    if (is_prime[i]) {
      int p = i;
      int a3 = p % 10;
      p /= 10;
      int a2 = p % 10;
      p /= 10;
      int a1 = p % 10;
      primes.push_back(std::tuple<int, int, int>(a1, a2, a3));
    }
  }
  return primes;
}

int main() {
  int n;
  std::cin >> n;
  if (n < 3 || n > MAX_N) {
    return 1;
  }

  std::vector<std::tuple<int, int, int>> primes = get_primes_from_100_to_1000();

  std::vector<int> ends_with_xx_counts(100, 0);
  for (auto &p : primes) {
    ends_with_xx_counts[std::get<1>(p) * 10 + std::get<2>(p)]++;
  }

  {
    std::vector<int> buffer(100);
    for (int i = 4; i <= n; ++i) {
      std::fill(std::begin(buffer), std::end(buffer), 0);
      for (auto &p : primes) {
        int xx = std::get<1>(p) * 10 + std::get<2>(p);
        buffer[xx] += ends_with_xx_counts[std::get<0>(p) * 10 + std::get<1>(p)];
        buffer[xx] %= MOD;
      }
      std::swap(buffer, ends_with_xx_counts);
    }
  }

  int answer = 0;
  for (int c : ends_with_xx_counts) {
    answer += c;
    answer %= MOD;
  }
  std::cout << answer;
  return 0;
}