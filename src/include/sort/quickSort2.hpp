#pragma once

#include <functional>
#include <utility>

namespace dsa {
template <typename IteratorType, typename CompFuncType>
auto partition3(IteratorType begin, IteratorType end, CompFuncType &&cmp)
    -> std::pair<IteratorType, IteratorType> {
  std::pair<IteratorType, IteratorType> bases(begin, end);
  IteratorType moving{begin + 1};

  while (moving != bases.second) {
    if (cmp(*moving, *begin)) {
      std::swap(*moving, *(++bases.first));

      ++moving;
    } else if (*moving == *begin) {
      ++moving;
    } else {
      std::swap(*moving, *(--bases.second));
    }
  }

  std::swap(*begin, *bases.first);

  return bases;
}

template <typename IteratorType,
          typename CompFuncType = std::less<
              typename std::iterator_traits<IteratorType>::value_type>>
void quickSort3(IteratorType begin, IteratorType end,
                CompFuncType &&cmp = CompFuncType{}) {
  if (end - begin < 2) {
    return;
  }

  std::pair<IteratorType, IteratorType> bases{dsa::partition3(begin, end, cmp)};

  quickSort3(begin, bases.first, cmp);
  quickSort3(bases.second, end, cmp);
}
} // namespace dsa