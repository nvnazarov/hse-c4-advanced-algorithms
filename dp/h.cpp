#include <climits>
#include <iostream>
#include <vector>

#define MASK_CONTAINS_PLANET_INDEX(mask, planet_index)                         \
  ((mask & (1 << planet_index)) != 0)
#define MASK_WITHOUT_PLANET_INDEX(mask, planet_index)                          \
  (mask & (~(1 << planet_index)))
#define MASK_OF_PLANET_INDEX(planet_index) (1 << planet_index)

struct Info {
  int min_cost;
  int next_planet_index;
  int next_mask;
};

int main() {
  int n;
  std::cin >> n;
  if (n < 1 || n > 19) {
    return 1;
  }

  std::vector<std::vector<int>> costs(n, std::vector<int>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> costs[i][j];
    }
  }

  int masks_count = 1 << n;
  std::vector<std::vector<Info>> dp(
      masks_count, std::vector<Info>(n, Info{.min_cost = INT_MAX}));
  for (int i = 0; i < n; ++i) {
    dp[MASK_OF_PLANET_INDEX(i)][i].min_cost = 0;
  }

  for (int mask = 1; mask < masks_count; ++mask) {
    for (int start_planet_index = 0; start_planet_index < n;
         ++start_planet_index) {
      if (!MASK_CONTAINS_PLANET_INDEX(mask, start_planet_index)) {
        continue;
      }
      int submask = MASK_WITHOUT_PLANET_INDEX(mask, start_planet_index);
      if (submask == 0) {
        continue;
      }
      for (int next_planet_index = 0; next_planet_index < n;
           ++next_planet_index) {
        if (!MASK_CONTAINS_PLANET_INDEX(submask, next_planet_index)) {
          continue;
        }
        int current_min_cost = dp[mask][start_planet_index].min_cost;
        int new_min_cost = dp[submask][next_planet_index].min_cost +
                           costs[start_planet_index][next_planet_index];
        if (new_min_cost < current_min_cost) {
          dp[mask][start_planet_index] = {.min_cost = new_min_cost,
                                          .next_planet_index =
                                              next_planet_index,
                                          .next_mask = submask};
        }
      }
    }
  }

  int start_planet_index = 0;
  int min_cost = dp[masks_count - 1][0].min_cost;
  for (int i = 1; i < n; ++i) {
    Info info = dp[masks_count - 1][i];
    if (min_cost > info.min_cost) {
      min_cost = info.min_cost;
      start_planet_index = i;
    }
  }

  std::cout << min_cost << "\n";
  int planet_index = start_planet_index;
  int mask = masks_count - 1;
  while (mask != 0) {
    std::cout << planet_index + 1 << " ";
    Info info = dp[mask][planet_index];
    mask = info.next_mask;
    planet_index = info.next_planet_index;
  }
}