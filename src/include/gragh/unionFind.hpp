#pragma once

#include <cstddef>
#include <vector>
namespace dsa {
    class unionFind {
    public:
        explicit unionFind(size_t size_);

        void connect(size_t indexA_, size_t indexB_);
        auto check(size_t indexA_, size_t indexB_) const -> bool;
    private:
        auto find(size_t index_) const -> size_t;

        std::vector<size_t> parent;
        std::vector<int> rank;
    };

    inline
    unionFind::unionFind(size_t size_)
    : parent(size_), rank(size_) {
        for (size_t i {}; i != size_; ++i) {
            parent[i] = i;
        }
    }

    inline
    void unionFind::connect(size_t indexA_, size_t indexB_) {
        size_t rootA {find(indexA_)};
        size_t rootB {find(indexB_)};

        if (rootA != rootB) {
            if (rank[rootA] < rank[rootB]) {
                parent[rootA] = rootB;
            } else if (rank[rootB] < rank[rootA]) {
                parent[rootB] = rootA;
            } else {
                parent[rootB] = rootA;
                ++rank[rootA];
            }
        }
    }

    inline
    auto unionFind::check(size_t indexA_, size_t indexB_) const -> bool {
        return find(indexA_) == find(indexB_);
    }

    inline
    auto unionFind::find(size_t index_) const -> size_t {
        while (parent[index_] != index_) {
            index_ = parent[index_];
        }

        return index_;
    }
}