#pragma once

#include <bits/stdc++.h>
#include "def.hpp"

namespace {
template<typename T>
using iter_val__ = typename std::iterator_traits<T>::value_type;
}

namespace ds {
template<typename TValue>
class SegmentTree {
private:
  long arr_size;
  TValue def_;
  std::vector<TValue> tree_;
  std::function<TValue(TValue, TValue)> func_;
public:
  SegmentTree(long size, TValue def = 0,
              std::function<TValue(TValue, TValue)> func = std::plus<TValue>()) CP_NOEXCEPT
      : arr_size(1 << (32 - __builtin_clz(size))),
        def_(def),
        tree_((arr_size << 1), def), func_(func) {}

  SegmentTree(std::vector<TValue> &&values, TValue def = 0,
              std::function<TValue(TValue, TValue)> func = std::plus<TValue>()) CP_NOEXCEPT
      : arr_size(values.size() >> 1),
        def_(def),
        tree_(std::move(values)),
        func_(func) {
    CP_ASSERT(__builtin_popcount(arr_size)==1 && "incorrect array length");
  }

  inline void set(long index, TValue val) CP_NOEXCEPT {
    CP_THROW_IF(index >= arr_size, std::out_of_range("index out of range"));
    index += arr_size;
    tree_[index] = val;
    for (index /= 2; index >= 1; index /= 2) {
      tree_[index] = func_(tree_[2*index], tree_[2*index + 1]);
    }
  }

  inline TValue get_range(TValue lhs, TValue rhs) CP_NOEXCEPT {
    CP_THROW_IF(lhs >= arr_size, std::out_of_range("lhs out of range"));
    CP_THROW_IF(rhs >= arr_size, std::out_of_range("rhs out of range"));
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

template<typename TIterator>
SegmentTree<iter_val__<TIterator>>
make_segment_tree(TIterator begin, TIterator end,
                  iter_val__<TIterator> def = 0,
                  std::function<iter_val__<TIterator>(iter_val__<TIterator>,
                                                      iter_val__<TIterator>)> func = std::plus<iter_val__<TIterator>>()
) CP_NOEXCEPT {
  static_assert(std::is_same<std::random_access_iterator_tag,
                             typename std::iterator_traits<TIterator>::iterator_category>::value);

  auto len(1 << (32 - __builtin_clz(std::distance(begin, end))));
  std::vector<iter_val__<TIterator>> values(len << 1, def);
  int i = len;
  for (auto iter = begin; iter!=end; ++iter, ++i) {
    values[i] = *iter;
  }
  for (i = len - 1; i > 0; --i) {
    values[i] = func(values[i << 1], values[(i << 1) + 1]);
  }
  return SegmentTree<iter_val__<TIterator>>(std::move(values), def, func);
}
}
