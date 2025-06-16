#pragma once

#include <memory>

template <typename keyType, typename valueType>
class bst {
    struct bstNode {
        keyType key {};
        valueType value {};

        bstNode * left {};
        bstNode * right {};
    };

    bstNode * root {};

    auto destory(bstNode * node) -> void {
        if (node) {
            destory(node->left);
            destory(node->right);

            delete node;
        }
    }

    auto insert__(bstNode * node, keyType const & key, valueType const & value) -> bstNode * {
        if (node) {
            if (node->key < key) {
                node->right = insert__(node->right, key, value);
            } else if (key < node->key) {
                node->left = insert__(node->left, key, value);
            } else {
                node->value = value;
            }

            return node;
        } else {
            return new bstNode {key, value};
        }
    }

    auto remove__(bstNode * node, keyType const & key) -> bstNode * {
        if (node->key < key) {
            node->right = remove__(node->right, key);
        } else if (key < node->key) {
            node->left = remove__(node->left, key);
        } else {
            if (!node->left) {
                bstNode * tmp {node};
                
                node = node->right;

                delete tmp;
            } else if (!node->right) {
                bstNode * tmp {node};

                node = node->left;

                delete node;
            } else {
                bstNode * newNode {findMaxNode__(node->left)};

                keyType newKey {newNode->key};
                valueType newValue {newNode->value};

                node->left = remove__(node->left, newKey);

                node->key = std::move(newKey);
                node->value = std::move(newValue);
            }

            return node;
        }
    }

    auto find__(bstNode * node, keyType const & key) const -> bstNode * {
        if (node) {
            if (node->key < key) {
                return find__(node->right, key);
            } else if (key < node->key) {
                return find__(node->left, key);
            } else {
                return node;
            }
        } else {
            return nullptr;
        }
    }

    auto findMaxNode__(bstNode * node) -> bstNode * {
        if (node) {
            if (node->right) {
                return findMaxNode__(node->right);
            } else {
                return node;
            }
        } else {
            return nullptr;
        }
    }

    auto findMinNode__(bstNode * node) -> bstNode * {
        if (node) {
            if (node->left) {
                return findMinNode__(node->left);
            } else {
                return node;
            }
        } else {
            return nullptr;
        }
    }

public:
    ~bst() {
        destory(root);
    }

    explicit
    bst() = default;

    auto insert(keyType const & key, valueType const & value) -> void {
        root = insert__(root, key, value);
    }

    auto find(keyType const & key) const -> valueType {
        bstNode * target {find__(root, key)};

        return target ? *target : valueType {};
    }

    auto remove(keyType const & key) -> void {
        bstNode * target {find__(root, key)};

        if (target) {
            root = remove__(root, key);
        }
    }
};