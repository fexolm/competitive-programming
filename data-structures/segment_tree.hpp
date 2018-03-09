#pragma once

#include <bits/stdc++.h>

namespace cp {
namespace ds {
template<typename TValue>
class SegmentTree {
private:
  size_t arr_size;
  TValue def_;
  std::vector<TValue> tree_;
  std::function<TValue(TValue, TValue)> func_;
public:
  SegmentTree(size_t size, TValue def = 0,
              std::function<TValue(TValue, TValue)> func = std::plus<TValue>())
      : arr_size(1 << (32 - __builtin_clz(size))),
        def_(def),
        tree_((arr_size << 1), def), func_(func) {}

  void set(size_t index, TValue val) {
    index += arr_size;
    tree_[index] = val;
    for (index /= 2; index >= 1; index /= 2) {
      tree_[index] = func_(tree_[2*index], tree_[2*index + 1]);
    }
  }

  TValue get_range(TValue lhs, TValue rhs) {
    lhs += arr_size;
    rhs += arr_size;
    TValue result = def_;
    while (lhs <= rhs) {
      if (lhs%2==1)
        result = func_(result, tree_[lhs++]);
      if (rhs%2==0)
        result = func_(result, tree_[rhs--]);
      lhs /= 2;
      rhs /= 2;
    }
    return result;
  }
};
}
}
