#include <cmath>
#include <iostream>
#include <vector>

const int MAX_N = 1e5;
const int MAX_K = 1e5;

struct Block {
  int l; // included
  int r; // not included
  int max_index;
  int max_value;

  bool is_inside(int l, int r) const { return this->l >= l && this->r <= r; }
  bool is_left(int l, int r) const { return this->l < l && this->r <= r; }
  bool is_right(int l, int r) const { return this->l >= l && this->r > r; }
};

int main() {
  int n;
  std::cin >> n;
  if (n < 1 || n > MAX_N) {
    return 1;
  }

  std::vector<int> array(n);
  for (int &a : array) {
    std::cin >> a;
  }

  int block_length = std::sqrt(n);
  std::vector<Block> blocks;
  {
    int blocks_count = (n - 1) / block_length + 1;
    blocks.reserve(blocks_count);
    for (int l = 0; l < n; l += block_length) {
      int r = std::min(n, l + block_length);
      int max_index = l;
      int max_value = array[l];
      for (int i = l + 1; i < r; ++i) {
        if (int value = array[i]; max_value < value) {
          max_index = i;
          max_value = value;
        }
      }
      blocks.push_back(Block{l, r, max_index, max_value});
    }
  }

  int k;
  std::cin >> k;
  if (k < 0 || k > MAX_K) {
    return 1;
  }

  while (k--) {
    int l, r;
    std::cin >> l >> r;

    if (l > r || l < 1 || r < 1 || l > n || r > n) {
      return 1;
    }

    l--;
    r--;
    int l_block_index = l / block_length;
    int r_block_index = r / block_length;

    int max_index = l;
    int max_value = array[l];

    for (int i = l_block_index; i <= r_block_index; ++i) {
      const Block &block = blocks[i];
      if (block.is_inside(l, r)) {
        if (max_value < block.max_value) {
          max_value = block.max_value;
          max_index = block.max_index;
        }
      } else if (block.is_left(l, r)) {
        for (int i = l; i < block.r; ++i) {
          if (int value = array[i]; max_value < value) {
            max_value = value;
            max_index = i;
          }
        }
      } else if (block.is_right(l, r)) {
        for (int i = block.l; i <= r; ++i) {
          if (int value = array[i]; max_value < value) {
            max_value = value;
            max_index = i;
          }
        }
      } else {
        for (int i = l; i <= r; ++i) {
          if (int value = array[i]; max_value < value) {
            max_value = value;
            max_index = i;
          }
        }
      }
    }

    std::cout << max_value << " " << max_index + 1 << "\n";
  }

  return 0;
}