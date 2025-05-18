#pragma once

#include <cstddef>
#include <vector>

namespace exp__ {
    class uf {
        std::vector<std::size_t> parent;
        std::vector<std::size_t> rank;

        auto find(std::size_t node) const -> std::size_t {
            if (parent.at(node) != node) {
                node = parent[node];
            }

            return node;
        }

    public:
        explicit
        uf(std::size_t nodeSize)
        : parent(nodeSize), rank(nodeSize, 1) {
            for (std::size_t i {}; i != parent.size(); ++i) {
                parent[i] = i;
            }
        }

        auto connect(std::size_t node1, std::size_t node2) -> void {
            std::size_t root1 {find(node1)};
            std::size_t root2 {find(node2)};

            if (root1 == root2) {
                return;
            }

            if (rank[root1] < rank[root2]) {
                parent[root1] = root2;
            } else if (rank[root2] < rank[root1]) {
                parent[root2] = root1;
            } else {
                parent[root2] = root1;

                ++rank[root1];
            }
        }

        auto check(std::size_t node1, std::size_t node2) const -> bool {
            return find(node1) == find(node2);
        }
    };
}