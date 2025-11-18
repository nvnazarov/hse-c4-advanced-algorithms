#include <cmath>
#include <iostream>

const int MAX_CUBES = 150;
const int MAX_LAYERS = 20;
const int MAX_TOP_LAYER_CUBES = MAX_CUBES;

int main() {
  int n;
  std::cin >> n;
  if (n < 1 || n > MAX_CUBES) {
    return 1;
  }

  int dp[MAX_CUBES + 1][MAX_LAYERS + 1][MAX_TOP_LAYER_CUBES + 1]{};
  dp[0][0][0] = 1;
  for (int i = 1; i < MAX_CUBES + 1; ++i) {
    dp[i][1][i] = 1;
  }
  for (int layers = 2; layers <= MAX_LAYERS; ++layers) {
    for (int cubes = layers * (layers + 1) / 2; cubes <= MAX_CUBES; ++cubes) {
      for (int top_layer_cubes = 1;
           top_layer_cubes <= std::min(MAX_TOP_LAYER_CUBES, cubes);
           ++top_layer_cubes) {
        for (int top_layer_cubes_substair = top_layer_cubes + 1;
             top_layer_cubes_substair <= MAX_TOP_LAYER_CUBES;
             ++top_layer_cubes_substair) {
          dp[cubes][layers][top_layer_cubes] +=
              dp[cubes - top_layer_cubes][layers - 1][top_layer_cubes_substair];
        }
      }
    }
  }

  int answer = 0;
  for (int i = 0; i <= MAX_LAYERS; ++i) {
    for (int j = 0; j <= MAX_TOP_LAYER_CUBES; ++j) {
      answer += dp[n][i][j];
    }
  }

  std::cout << answer;
}