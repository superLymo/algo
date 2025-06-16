#pragma once

#include "gragh.hpp"

#include <queue>

namespace dsa {
    template <typename ValueType>
    class bfs {
    public:
        ~bfs() {
            delete [] visited;
        }
        bfs(bfs const &) = delete;
        bfs & operator=(bfs const &) = delete;

        explicit bfs(gragh<ValueType> const & g_)
        : g(g_), visited(new bool [g_.getNodeSize()]) {}

        auto run(size_t startPos) -> std::vector<size_t> {
            for (size_t i {}; i != g.getNodeSize(); ++i) {
                visited[i] = false;
            }

            std::deque<size_t> nodes;
            nodes.push_back(startPos);
            visited[startPos] = true;

            std::vector<size_t> steps(g.getNodeSize());

            while (!nodes.empty()) {
                std::vector<ValueType> edges(g.getEdges(nodes.front()));

                for (size_t i {}; i != edges.size(); ++i) {
                    if (edges[i] != ValueType{} && !visited[i]) {
                        nodes.push_back(i);
                        visited[i] = true;
                        steps[i] = steps[nodes.front()] + 1;
                    }
                }

                nodes.pop_front();
            }

            return steps;
        }
    private:
        gragh<ValueType> const & g;
        bool * visited;
    };
}