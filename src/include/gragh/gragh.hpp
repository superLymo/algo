#pragma once

#include <vector>
#include <cstddef>

namespace dsa {
    template <typename ValueType>
    class gragh {
    public:
        explicit gragh(size_t nodeSize, bool hasDerection = false);

        auto getEdgeSize() const -> size_t;
        auto getNodeSize() const -> size_t;

        void setEdge(size_t from, size_t to, ValueType value);
        auto getEdges(size_t from) const -> std::vector<ValueType> const &;
    private:
        std::vector<std::vector<ValueType>> edges;
        bool direction;
    };

    template<typename ValueType>
    gragh<ValueType>::gragh(size_t nodeSize, bool hasDerection)
    :edges(nodeSize, std::vector<ValueType>(nodeSize)), direction(hasDerection) {}

    template<typename ValueType>
    auto gragh<ValueType>::getEdgeSize() const -> size_t {
        size_t edgeCnt {};

        for (auto const & i : edges) {
            for (auto const & j : i) {
                if (j != ValueType()) {
                    ++edgeCnt;
                }
            }
        }

        if (!direction) {
            edgeCnt >>= 1;
        }

        return edgeCnt;
    }

    template<typename ValueType>
    auto gragh<ValueType>::getNodeSize() const -> size_t {
        return edges.size();
    }

    template <typename ValueType>
    void gragh<ValueType>::setEdge(size_t from, size_t to, ValueType value) {
        edges.at(from).at(to) = value;

        if (!direction) {
            edges.at(to).at(from) = value;
        }
    }

    template<typename ValueType>
    auto gragh<ValueType>::getEdges(size_t from) const -> std::vector<ValueType> const & {
        return edges.at(from);
    }

    template <typename ValueType>
    struct edge {
        explicit edge()
        : from {}, to {}, value {} {}
        explicit edge(size_t from_, size_t to_, ValueType value_ )
        : from(from_), to(to_), value(std::move(value_)) {}

        auto operator<(edge const & e_) const -> bool {
            return value < e_.value;
        }

        size_t from;
        size_t to;
        ValueType value;
    };
}