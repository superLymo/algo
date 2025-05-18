#include <vector>
#include <cassert>
#include <./binary/binarySearch.hpp>

// Test cases for binarySearch
void testBinarySearch() {
    // Test empty container
    {
        std::vector<int> empty;
        auto result = binarySearch(empty.begin(), empty.end(), 42);
        assert(result == decltype(empty)::iterator{});
    }

    // Test single element container (found)
    {
        std::vector<int> single{42};
        auto result = binarySearch(single.begin(), single.end(), 42);
        assert(result == single.begin());
    }

    // Test single element container (not found)
    {
        std::vector<int> single{42};
        auto result = binarySearch(single.begin(), single.end(), 24);
        assert(result == decltype(single)::iterator{});
    }

    // Test even number of elements (found)
    {
        std::vector<int> even{1, 2, 3, 4, 5, 6};
        auto target = 4;
        auto result = binarySearch(even.begin(), even.end(), target);
        assert(result != even.end());
        assert(*result == target);
    }

    // Test even number of elements (not found)
    {
        std::vector<int> even{1, 2, 3, 4, 5, 6};
        auto result = binarySearch(even.begin(), even.end(), 7);
        assert(result == decltype(even)::iterator{});
    }

    // Test odd number of elements (found)
    {
        std::vector<int> odd{1, 2, 3, 4, 5};
        auto target = 3;
        auto result = binarySearch(odd.begin(), odd.end(), target);
        assert(result != odd.end());
        assert(*result == target);
    }

    // Test odd number of elements (not found)
    {
        std::vector<int> odd{1, 2, 3, 4, 5};
        auto result = binarySearch(odd.begin(), odd.end(), 0);
        assert(result == decltype(odd)::iterator{});
    }

    // Test first element
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        auto result = binarySearch(vec.begin(), vec.end(), 1);
        assert(result == vec.begin());
    }

    // Test last element
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        auto result = binarySearch(vec.begin(), vec.end(), 5);
        assert(result == vec.end() - 1);
    }

    // Test middle element
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        auto result = binarySearch(vec.begin(), vec.end(), 3);
        assert(result == vec.begin() + 2);
    }

    // Test duplicate elements (should return first occurrence)
    {
        std::vector<int> dup{1, 2, 2, 2, 3};
        auto target = 2;
        auto result = binarySearch(dup.begin(), dup.end(), target);
        assert(result != dup.end());
        assert(*result == target);
        assert(result == dup.begin() + 1); // First occurrence
    }
}

// int main() {
//     testBinarySearch();
//     return 0;
// }
