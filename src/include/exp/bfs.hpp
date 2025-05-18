#pragma once

#include <queue>

#include "gragh.hpp"

namespace exp__ {
    template <typename weightType>
    class bfs {
        gragh<weightType> & g;
        bool * visited;

    public:
        ~bfs() {
            delete [] visited;
        }

        bfs(bfs const &) = delete;
        auto operator=(bfs const &) -> bfs & = delete;

        explicit
        bfs(gragh<weightType> & g__)
        : g(g__), visited {new bool[g__.getSize()]} {
            for (std::size_t i {}; i != g.getSize(); ++i) {
                visited[i] = false;
            }
        }

        auto operator()(std::size_t startNode) -> void {
            std::queue<std::size_t> nodes;

            nodes.emplace(startNode);

            while (!nodes.empty()) {
                std::size_t node {nodes.front()};
                nodes.pop();

                visited[node] = true;

                auto const & edges {g.getEdgesByNode(node)};

                for (std::size_t i {}; i != g.getSize(); ++i) {
                    if (edges[i] != weightType {} && !visited[node]) {
                        nodes.emplace(i);
                    }
                }
            }
        }
    };
}