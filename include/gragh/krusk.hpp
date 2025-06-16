#pragma once

#include "gragh.hpp"
#include "unionFind.hpp"

#include <deque>
#include <algorithm>

namespace dsa {
    template <typename ValueType>
    auto krusk(gragh<ValueType> const & g) -> std::vector<edge<ValueType>> {
        std::deque<edge<ValueType>> edges;

        for (size_t i {}; i != g.getNodeSize(); ++i) {
           std::vector<ValueType> const & vec(g.getEdges(i));

           for (size_t j {}; j != vec.size(); ++j) {
               if (vec[j] != ValueType{} && i < j) {
                   edges.emplace_back(i, j, vec[j]);
               }
           }
        }

        std::sort(edges.begin(), edges.end());

        unionFind uf(g.getNodeSize());
        std::vector<edge<ValueType>> res;

        while (!edges.empty()) {
            if (!uf.check(edges.front().from, edges.front().to)) {
                uf.connect(edges.front().from, edges.front().to);
                res.emplace_back(std::move(edges.front()));
            }

            edges.pop_front();
        }

        return res;
    }
}