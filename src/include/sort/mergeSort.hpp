#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace dsa {
template <typename IteratorType, typename CompFuncType>
void mergeOperation(IteratorType begin, IteratorType end, CompFuncType cmp) {
  std::vector<typename std::iterator_traits<IteratorType>::value_type> local;

  for (IteratorType i{begin}; i != end; ++i) {
    local.emplace_back(std::move(*i));
  }

  IteratorType lBegin{local.begin()};
  IteratorType rBegin{((local.end() - local.begin()) >> 1) + local.begin()};
  IteratorType lEnd{rBegin};

  for (IteratorType i{begin}; i != end; ++i) {
    if (lBegin == lEnd) {
      *i = std::move(*rBegin);
      ++rBegin;

      continue;
    }

    if (rBegin == local.end()) {
      *i = std::move(*lBegin);
      ++lBegin;

      continue;
    }

    if (cmp(*lBegin, *rBegin)) {
      *i = std::move(*lBegin);
      ++lBegin;
    } else {
      *i = std::move(*rBegin);
      ++rBegin;
    }
  }
}

template <typename IteratorType,
          typename CompFuncType = std::less<
              typename std::iterator_traits<IteratorType>::value_type>>
void mergeSort(IteratorType begin, IteratorType end,
               CompFuncType cmp = CompFuncType{}) {
  if (end - begin < 2) {
    return;
  }

  IteratorType mid{((end - begin) >> 1) + begin};

  mergeSort(begin, mid, cmp);
  mergeSort(mid, end, cmp);

  if (cmp(*mid, *(mid - 1))) {
    mergeOperation(begin, end, cmp);
  }
}
} // namespace dsa