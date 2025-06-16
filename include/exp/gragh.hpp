#pragma once

#include <vector>

namespace exp__ {
    template <typename weightType>
    class gragh {
        std::vector<std::vector<weightType>> allEdges;
        bool isDirected;

    public:
        explicit
        gragh(std::size_t nodeSize, bool direct = false)
        : allEdges(nodeSize, std::vector<weightType>(nodeSize)), isDirected(direct){ }

        auto addEdge(std::size_t node1, std::size_t node2, weightType const & weight) -> void {
            allEdges.at(node1).at(node2) = weight;

            if (!isDirected) {
                allEdges.at(node2).at(node1) = weight;
            }
        }

        auto getSize() const -> std::size_t {
            return allEdges.size();
        }

        auto getEdgesByNode(std::size_t node) const -> std::vector<weightType> const & {
            return allEdges.at(node);
        }
    };
}
