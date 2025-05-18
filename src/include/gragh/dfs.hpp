#pragma once

#include "gragh.hpp"

namespace dsa {
    template <typename ValueType>
    class dfs {
    public:
        ~dfs() {
            delete [] visited;
        }
        dfs(dfs const &) = delete;
        dfs & operator=(dfs const &) = delete;

        explicit dfs(gragh<ValueType> const & g_)
        : g(g_), visited(new bool [g_.getNodeSize()]) {}

        auto run() -> size_t {
            for (size_t i {}; i != g.getNodeSize(); ++i) {
                visited[i] = false;
            }

            size_t cnt {};

            for (size_t i {}; i != g.getNodeSize(); ++i) {
                if (!visited[i]) {
                    visit(i);

                    ++cnt;
                }
            }

            return cnt;
        }
    private:
        void visit(size_t nowPos) {
            visited[nowPos] = true;

            std::vector<ValueType> edges(g.getEdges(nowPos));

            for (size_t i {}; i != edges.size(); ++i) {
                if (edges[i] != ValueType{} && !visited[i]) {
                    visit(i);
                }
            }
        }

        gragh<ValueType> const & g;
        bool * visited;
    };
}