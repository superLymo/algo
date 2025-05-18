#include <vector>
#include <functional>
#include <iterator>
#include <type_traits>

template <typename eleType, typename compType = std::less<eleType>>
class heap {
    std::vector<eleType> data;
    compType comp;

    auto shiftDown(std::size_t index) -> void {
        auto tmp {std::move(data[index])};

        while ((index << 1) + 1 < data.size()) {
            std::size_t son {(index << 1) + 1};

            if (son + 1 < data.size() && comp(data[son + 1], data[son])) {
                ++son;
            }

            if (comp(data[son], tmp)) {
                data[index] = std::move(data[son]);

                index = son;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }

    auto shiftUp(std::size_t index) -> void {
        auto tmp {std::move(data[index])};

        while (index != 0) {
            if (comp(tmp, data[(index - 1) >> 1])) {
                data[index] = std::move(data[(index - 1) >> 1]);

                index = (index - 1) >> 1;
            } else {
                break;
            }
        }

        data[index] = std::move(tmp);
    }

public:
    explicit
    heap(compType comp__ = compType {})
    : comp(comp__) { }

    explicit
    heap(auto begin, auto end, compType comp__ = compType {})
    : data(begin, end), comp(comp__) {
        for (auto i {(data.size() - 2) >> 1}; i != -1; --i) {
            shiftDown(i);
        }
    }

    auto size() const -> std::size_t {
        return data.size();
    }

    auto empty() const -> bool {
        return data.empty();
    }

    auto insert(eleType const & ele) -> void {
        data.emplace_back(ele);

        shiftUp(data.size() - 1);
    }

    auto extract() -> eleType {
        if (!empty()) {
            eleType toRet {std::move(data.front())};

            data.front() = std::move(data.back());
            data.pop_back();

            shiftDown(0);

            return toRet;
        }

        return eleType {};
    }
};