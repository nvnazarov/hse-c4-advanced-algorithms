#include <iostream>

#define CHECK_SIDE_SIZE(x)                                                     \
  if (x < 1 || x > 5000) {                                                     \
    return 1;                                                                  \
  }

int grundy(int x) {
  while (x % 2 == 1) {
    x /= 2;
  }
  return x / 2;
}

int main() {
  int a, b, c;
  std::cin >> a >> b >> c;
  CHECK_SIDE_SIZE(a)
  CHECK_SIDE_SIZE(b)
  CHECK_SIDE_SIZE(c)

  // We can cosider the task as three separate games.
  // Each game is defined as the following:
  // 1. We have a side of size X
  // 2. At each turn, a player can reduce the side's size by at most
  //    floor(X/2)
  // 3. A player who cannot make a move loses

  if ((grundy(a) ^ grundy(b) ^ grundy(c)) == 0) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    for (int sa = (a - 1) / 2 + 1; sa < a; ++sa) {
      if ((grundy(sa) ^ grundy(b) ^ grundy(c)) == 0) {
        std::cout << sa << " " << b << " " << c << "\n";
        return 0;
      }
    }
    for (int sb = (b - 1) / 2 + 1; sb < b; ++sb) {
      if ((grundy(a) ^ grundy(sb) ^ grundy(c)) == 0) {
        std::cout << a << " " << sb << " " << c << "\n";
        return 0;
      }
    }
    for (int sc = (c - 1) / 2 + 1; sc < c; ++sc) {
      if ((grundy(a) ^ grundy(b) ^ grundy(sc)) == 0) {
        std::cout << a << " " << b << " " << sc << "\n";
        return 0;
      }
    }
  }

  return 0;
}