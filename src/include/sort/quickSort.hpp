#pragma once

#include <functional>

namespace dsa {
template <typename IteratorType, typename CompFuncType>
auto partition(IteratorType begin, IteratorType end, CompFuncType &&cmp)
    -> IteratorType {
  std::swap(*begin, *(((end - begin) >> 1) + begin));

  IteratorType saver{begin};
  IteratorType moving{begin + 1};

  while (moving != end) {
    if (cmp(*moving, *begin)) {
      std::swap(*(++saver), *moving);
    }

    ++moving;
  }

  std::swap(*saver, *begin);

  return saver;
}

template <typename IteratorType,
          typename CompFuncType = std::less<
              typename std::iterator_traits<IteratorType>::value_type>>
void quickSort(IteratorType begin, IteratorType end,
               CompFuncType &&cmp = CompFuncType{}) {
  if (end - begin < 2) {
    return;
  }

  IteratorType base{dsa::partition(begin, end, cmp)};

  quickSort(begin, base, cmp);
  quickSort(base + 1, end, cmp);
}
} // namespace dsa