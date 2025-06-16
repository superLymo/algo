#pragma once

#include <algorithm>
#include <cstddef>

namespace dsa {
    /**
     * @brief 二叉搜索树节点的结构体模板
     * 
     * @tparam KeyType 键的类型
     * @tparam ValueType 值的类型
     */
    template <typename KeyType, typename ValueType>
    struct bstNode {
        KeyType key;       // 节点存储的键
        ValueType value;   // 节点存储的值
        bstNode * left;    // 指向左子节点的指针
        bstNode * right;   // 指向右子节点的指针
    };

    /**
     * @brief 二叉搜索树的类模板
     * 
     * @tparam keyType 键的类型
     * @tparam valueType 值的类型
     */
    template <typename keyType, typename valueType>
    class bst {
        bstNode<keyType, valueType> * root;  // 指向二叉搜索树根节点的指针
        std::size_t nodeSum;                 // 二叉搜索树中节点的数量

    public:
        /**
         * @brief 析构函数，用于释放二叉搜索树占用的内存
         */
        ~bst() {
            destory(root);  // 调用私有成员函数销毁整棵树
        }

        /**
         * @brief 显式构造函数，初始化一棵空的二叉搜索树
         */
        explicit bst() : root(nullptr), nodeSum {} {}

        /**
         * @brief 获取二叉搜索树中节点的数量
         * 
         * @return std::size_t 节点的数量
         */
        auto size() const -> std::size_t {
            return nodeSum;
        }

        /**
         * @brief 判断二叉搜索树是否为空
         * 
         * @return bool 若为空返回 true，否则返回 false
         */
        auto empty() const -> bool {
            return nodeSum == 0;
        }

        /**
         * @brief 向二叉搜索树中插入一个键值对
         * 
         * @param key 要插入的键
         * @param value 要插入的值
         */
        void insert(keyType key, valueType value) {
            root = insert(root, key, value);  // 调用私有成员函数进行插入操作
        }

        /**
         * @brief 判断二叉搜索树中是否包含指定的键
         * 
         * @param key 要查找的键
         * @return bool 若包含返回 true，否则返回 false
         */
        auto contain(keyType const & key) const -> bool {
            return find(root, key) != nullptr;  // 调用私有成员函数查找节点
        }

        /**
         * @brief 获取指定键对应的值
         * 
         * @param key 要查找的键
         * @return valueType const& 键对应的值的常量引用
         */
        auto getValue(keyType key) const -> valueType const & {
            return find(root, key)->value;  // 调用私有成员函数查找节点并返回值
        }

        /**
         * @brief 从二叉搜索树中移除指定键对应的节点
         * 
         * @param key 要移除的节点的键
         */
        void remove(keyType const & key) {
            if (contain(key)) {  // 先判断树中是否包含该键
                root = remove(root, key);  // 调用私有成员函数进行移除操作
                --nodeSum;  // 节点数量减 1
            }
        }

    private:
        /**
         * @brief 递归销毁以指定节点为根的子树
         * 
         * @param node 要销毁的子树的根节点
         */
        void destory(bstNode<keyType, valueType> * node) {
            if (node) {  // 若节点不为空
                destory(node->left);   // 递归销毁左子树
                destory(node->right);  // 递归销毁右子树
                delete node;           // 释放当前节点的内存
            }
        }

        /**
         * @brief 递归地向以指定节点为根的子树中插入一个键值对
         * 
         * @param node 子树的根节点
         * @param key 要插入的键
         * @param value 要插入的值
         * @return bstNode<keyType, valueType>* 插入操作后的子树根节点
         */
        auto insert(bstNode<keyType, valueType> * node, keyType & key, valueType & value)
        -> bstNode<keyType, valueType> * {
            if (!node) {  // 若当前节点为空，创建新节点
                ++nodeSum;
                return new bstNode<keyType, valueType> {std::move(key), std::move(value)};
            }

            if (node->key < key) {  // 若键大于当前节点的键，插入到右子树
                node->right = insert(node->right, key, value);
            } else if (key < node->key) {  // 若键小于当前节点的键，插入到左子树
                node->left = insert(node->left, key, value);
            } else {  // 若键相等，更新节点的值
                node->value = std::move(value);
            }

            return node;
        }

        /**
         * @brief 递归地在以指定节点为根的子树中查找指定键对应的节点
         * 
         * @param node 子树的根节点
         * @param key 要查找的键
         * @return bstNode<keyType, valueType>* 若找到返回节点指针，否则返回 nullptr
         */
        auto find(bstNode<keyType, valueType> * node, keyType const & key) const
        -> bstNode<keyType, valueType> * {
            if (!node) {  // 若当前节点为空，返回 nullptr
                return nullptr;
            }

            if (node->key < key) {  // 若键大于当前节点的键，在右子树中查找
                return find(node->right, key);
            } else if (key < node->key) {  // 若键小于当前节点的键，在左子树中查找
                return find(node->left, key);
            } else {  // 若键相等，返回当前节点
                return node;
            }
        }

        /**
         * @brief 递归地在以指定节点为根的子树中查找键值最大的节点
         * 
         * @param node 子树的根节点
         * @return bstNode<keyType, valueType>* 键值最大的节点指针，若为空树返回 nullptr
         */
        auto findMaxNode(bstNode<keyType, valueType> * node)
        -> bstNode<keyType, valueType> * {
            if (!node) {  // 若当前节点为空，返回 nullptr
                return nullptr;
            }

            if (node->right) {  // 若右子节点存在，在右子树中继续查找
                return findMaxNode(node->right);
            } else {  // 否则当前节点即为键值最大的节点
                return node;
            }
        }

        /**
         * @brief 递归地在以指定节点为根的子树中查找键值最小的节点
         * 
         * @param node 子树的根节点
         * @return bstNode<keyType, valueType>* 键值最小的节点指针，若为空树返回 nullptr
         */
        auto findMinNode(bstNode<keyType, valueType> * node)
        -> bstNode<keyType, valueType> * {
            if (!node) {  // 若当前节点为空，返回 nullptr
                return nullptr;
            }

            if (node->left) {  // 若左子节点存在，在左子树中继续查找
                return findMinNode(node->left);
            } else {  // 否则当前节点即为键值最小的节点
                return node;
            }
        }

        /**
         * @brief 递归地从以指定节点为根的子树中移除指定键对应的节点
         * 
         * @param node 子树的根节点
         * @param key 要移除的节点的键
         * @return bstNode<keyType, valueType>* 移除操作后的子树根节点
         */
        auto remove(bstNode<keyType, valueType> * node, keyType const & key)
        -> bstNode<keyType, valueType> * {
            if (node->key < key) {  // 若键大于当前节点的键，在右子树中移除
                node->right = remove(node->right, key);
            } else if (key < node->key) {  // 若键小于当前节点的键，在左子树中移除
                node->left = remove(node->left, key);
            } else {  // 找到要移除的节点
                if (!node->left) {  // 若左子节点为空，用右子节点替换当前节点
                    bstNode<keyType, valueType> * tmp {node};
                    node = node->right;
                    delete tmp;
                } else if (!node->right) {  // 若右子节点为空，用左子节点替换当前节点
                    bstNode<keyType, valueType> * tmp {node};
                    node = node->left;
                    delete tmp;
                } else {  // 若左右子节点都存在，用左子树中键值最大的节点替换当前节点
                    bstNode<keyType, valueType> * tmp {findMaxNode(node->left)};
                    keyType key_ {tmp->key};
                    valueType value_ {tmp->value};
                    node->left = remove(node->left, key_);
                    node->key = std::move(key_);
                    node->value = std::move(value_);
                }
            }

            return node;
        }
    };
}