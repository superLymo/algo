#pragma once

#include <functional>

namespace dsa {
template <typename IteratorType,
          typename Comp = std::less<
              typename std::iterator_traits<IteratorType>::value_type>>
void selectionSort(IteratorType begin, IteratorType end, Comp cmp = Comp{}) {
  if (end - begin < 1) {
    return;
  }

  for (IteratorType i{begin}; i != end; ++i) {
    IteratorType flag{i};

    for (IteratorType j{i + 1}; j != end; ++j) {
      if (cmp(*j, *flag)) {
        flag = j;
      }
    }

    std::swap(*i, *flag);
  }
}
} // namespace dsa