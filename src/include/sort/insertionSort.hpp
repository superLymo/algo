#pragma once

#include <functional>

namespace dsa {
template <typename IteratorType,
          typename Comp = std::less<
              typename std::iterator_traits<IteratorType>::value_type>>
void insertionSort(IteratorType begin, IteratorType end, Comp cmp = Comp{}) {
  if (end - begin < 2) {
    return;
  }

  for (IteratorType i{begin + 1}; i != end; ++i) {
    typename std::iterator_traits<IteratorType>::value_type temp{std::move(*i)};
    IteratorType moving{i};

    while (moving != begin) {
      if (cmp(temp, *(moving - 1))) {
        *moving = std::move(*(moving - 1));
        --moving;
      } else {
        break;
      }
    }

    *moving = std::move(temp);
  }
}
} // namespace dsa