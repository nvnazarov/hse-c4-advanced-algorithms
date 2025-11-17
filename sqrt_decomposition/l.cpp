#include <cmath>
#include <iostream>
#include <vector>

class WaterSupply {
  struct Block {
    int l; // included
    int r; // excluded
    int add;
    int max_flow;

    bool is_inside(int l, int r) const {
      return this->l >= l && this->r <= r + 1;
    }
  };

  int pipes_count;
  int max_flow;
  int block_length;
  std::vector<int> pipes_flows;
  std::vector<Block> blocks;

  bool can_open_flow(int l, int r) {
    r--;
    int l_block_index = l / block_length;
    int r_block_index = r / block_length;
    for (int i = l_block_index; i <= r_block_index; ++i) {
      if (const Block &b = blocks[i]; b.is_inside(l, r)) {
        if (b.max_flow + b.add >= max_flow) {
          return false;
        }
      } else {
        for (int j = std::max(l, b.l); j <= std::min(r, b.r - 1); ++j) {
          if (pipes_flows[j] + b.add >= max_flow) {
            return false;
          }
        }
      }
    }
    return true;
  }

  void increase_flow(int l, int r) {
    r--;
    int l_block_index = l / block_length;
    int r_block_index = r / block_length;
    for (int i = l_block_index; i <= r_block_index; ++i) {
      if (Block &b = blocks[i]; b.is_inside(l, r)) {
        b.add++;
      } else {
        for (int j = std::max(l, b.l); j <= std::min(r, b.r - 1); ++j) {
          pipes_flows[j]++;
          b.max_flow = std::max(b.max_flow, pipes_flows[j]);
        }
      }
    }
  }

public:
  WaterSupply(int pipes_count, int max_flow)
      : pipes_count(pipes_count), max_flow(max_flow), pipes_flows(pipes_count),
        block_length(std::sqrt(pipes_count)) {
    int blocks_count = (pipes_count - 1) / block_length + 1;
    blocks.reserve(blocks_count);
    for (int l = 0; l < pipes_count; l += block_length) {
      int r = std::min(pipes_count, l + block_length);
      blocks.push_back(Block{l, r, 0, 0});
    }
  }

  bool open_flow(int l, int r) {
    if (l < 0 || l >= r || r > this->pipes_count) {
      exit(1);
    }
    if (can_open_flow(l, r)) {
      increase_flow(l, r);
      return true;
    }
    return false;
  }
};

int main() {
  const int MAX_N = 200'000;
  const int MAX_K = 1'000;
  const int MAX_M = 100'000;

  int n, k, m;
  std::cin >> n >> k >> m;
  if (n < 1 || k < 1 || m < 1 || n > MAX_N || k > MAX_K || m > MAX_M) {
    return 1;
  }
  WaterSupply water_supply(n, k);
  while (m--) {
    int l, r;
    std::cin >> l >> r;
    std::cout << static_cast<int>(water_supply.open_flow(l, r)) << "\n";
  }
  return 0;
}