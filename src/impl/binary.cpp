#include <iterator>
#include <optional>

auto binarySeatch(auto begin, auto end, auto const & target) {
    while (begin != end) {
        auto mid {std::next(begin, std::distance(begin, end) >> 1)};

        if (*mid < target) {
            begin = std::next(mid);
        } else if (target < *mid) {
            end = mid;
        } else {
            return mid;
        }
    }

    return decltype(begin) {};
}

template <typename keyType, typename valueType>
class bst {
    struct node {
        keyType key {};
        valueType value {};
        node * left {};
        node * right {};
    };

    node * root {};

    auto destory(node * p) -> void {
        if (p) {
            destory(p->left);
            destory(p->right);

            delete p;
        }
    }

    auto find(node * p, keyType const & key) -> node * {
        if (p) {
            if (p->key < key) {
                return find(p->right, key);
            } else if (key < p->key) {
                return find(p->left, key);
            } else {
                return p;
            }
        } else {
            return nullptr;
        }
    }

    auto findMaxNode(node * p) -> node * {
        if (p) {
            return p->right ? findMaxNode(p->right) : p;
        }

        return nullptr;
    }

    auto insert(node * p, keyType const & key, valueType const & value) -> node * {
        if (p) {
            if (p->key < key) {
                p->right = insert(p->right, key, value);
            } else if (key < p->key) {
                p->left = insert(p->left, key, value);
            } else {
                p->value = value;
            }

            return p;
        } else {
            return new node {key, value};
        }
    }

    auto remove(node * p, keyType const & key) -> node * {
        if (p->key < key) {
            p->right = remove(p->right, key);
        } else if (key < p->key) {
            p->left = remove(p->left, key);
        } else {
            if (!p->left) {
                node * tmp {p};

                p = p->right;

                delete tmp;
            } else if (!p->right) {
                node * tmp {p};

                p = p->left;

                delete tmp;
            } else {
                auto tmp {findMaxNode(p->left)};

                auto tmpKey {tmp->key};
                auto tmpValue {tmp->value};

                p->left = remove(p->left, tmpKey);

                p->key = std::move(tmpKey);
                p->value = std::move(tmpValue);
            }
        }

        return p;
    }
public:
    ~bst() {
        if (root) {
            destory(root);
        }
    }

    bst(bst const &) = delete;
    auto operator=(bst const &) -> bst & = delete;

    explicit
    bst() = default;

    auto insert(keyType const & key, valueType const & value) -> void {
        root = insert(root, key, value);
    }

    auto remove(keyType const & key) -> void {
        if (find(root, key)) {
            root = remove(root, key);
        }
    }

    auto find(keyType const & key) -> std::optional<valueType> {
        auto res {find(root, key)};

        if (res) {
            return *res;
        } else {
            return std::nullopt;
        }
    }
};