#pragma once

#include <queue>

#include "gragh.hpp"

namespace exp__ {
    template <typename weightType>
    class dfs {
        gragh<weightType> & g;
        bool * visited;
        std::size_t cnt {};

        auto operator()(std::size_t index) -> void {
            visited[index] = true;

            std::vector<weightType> edges(g.getEdgesByNode(index));

            for (std::size_t i {}; i != edges.size(); ++i) {
                if (edges[i] != weightType {} && !visited[i]) {
                    operator()(i);
                }
            }
        }

    public:
        ~dfs() {
            delete [] visited;
        }

        dfs(dfs const &) = delete;
        auto operator=(dfs const &) -> dfs & = delete;

        explicit
        dfs(gragh<weightType> & g__)
        : g(g__), visited {new bool[g__.getSize()]} {
            for (std::size_t i {}; i != g.getSize(); ++i) {
                visited[i] = false;
            }

            for (std::size_t i {}; i != g.getSize(); ++i) {
                if (!visited[i]) {
                    ++cnt;

                    operator()(i);
                }
            }
        }
    };
}