#pragma once

#include <vector>
#include <algorithm>

#include "unionFind.hpp"
#include "gragh.hpp"

namespace exp__ {
    template <typename weightType>
    struct edge {
        std::size_t from {};
        std::size_t to {};
        weightType weight {};
    };

    template <typename weightType>
    auto krusk(gragh<weightType> const & g) -> std::vector<edge<weightType>> {
        std::vector<edge<weightType>> allEdges;

        for (std::size_t i {}; i != g.getSize(); ++i) {
            auto const & edges {g.getEdgesByNode(i)};

            for (std::size_t j {}; j != g.getSize(); ++j) {
                if (edges[j] != weightType {} && i > j) {
                    allEdges.emplace_back(i, j, edges[j]);
                }
            }
        }

        std::sort(allEdges.begin(), allEdges.end(), [](edge<weightType> const & e1, edge<weightType> const & e2){
           return e1.weight < e2.weight;
        });

        uf fff(g.getSize());

        std::vector<edge<weightType>> toRet;

        for (auto const & e : allEdges) {
            if (!fff.check(e.from, e.to)) {
                toRet.emplace_back(e);

                fff.connect(e.from, e.to);
            }
        }

        return toRet;
    }
}