#pragma once

#include <cstddef>

namespace dsa {
    /**
     * @brief 单向链表节点的结构体模板
     * 
     * @tparam ValueType 节点存储的值的类型
     */
    template <typename ValueType>
    struct listNode {
        ValueType value;  // 节点存储的值
        listNode * next;  // 指向下一个节点的指针
    };

    /**
     * @brief 单向链表类模板
     * 
     * @tparam ValueType 链表存储的值的类型
     */
    template <typename ValueType>
    class forwardList {
        listNode<ValueType> * root;  // 链表的头节点指针
        listNode<ValueType> * far;   // 链表的尾节点指针
        listNode<ValueType> mutable * before;  // 用于定位节点的可变指针

        /**
         * @brief 定位到指定索引的前一个节点
         * 
         * @param index_ 要定位的节点的索引
         */
        void locate(std::size_t index_) const {
            // 检查索引是否越界，如果越界则将 before 置为 nullptr
            if (size() + 1 < index_) {
                before = nullptr;

                return;
            }

            before = root;  // 从根节点开始
            
            // 遍历链表，直到到达指定索引的前一个节点
            for (std::size_t i {1}; i != index_; ++i) {
                before = before->next;
            }
        }

        /**
         * @brief 反转从 from_ 到 to_ 之间的节点
         * 
         * @param from_ 反转区间的起始节点
         * @param to_ 反转区间的结束节点
         * @return listNode<ValueType>* 反转后的新的起始节点
         */
        auto reversing(listNode<ValueType> * from_, listNode<ValueType> * to_)
        -> listNode<ValueType> * {
            // 如果 from_ 不等于 to_，递归反转后续节点
            if (from_ != to_) {
                reversing(from_->next, to_)->next = from_;
            }

            return from_;
        }

    public:
        /**
         * @brief 析构函数，释放链表中所有节点的内存
         */
        ~forwardList() {
            // 循环删除链表中的节点，直到根节点为空
            while (root) {
                listNode<ValueType> * tmp {root};
                root = root->next;

                delete tmp;
            }
        }

        // 禁用拷贝构造函数
        forwardList(forwardList const &) = delete;
        // 禁用赋值运算符
        forwardList & operator=(forwardList const &) = delete;

        /**
         * @brief 构造函数，初始化链表
         */
        forwardList()
        : root {new listNode<ValueType>} {
            far = root;  // 初始化尾节点为根节点
        }

        /**
         * @brief 获取链表的长度
         * 
         * @return std::size_t 链表的长度
         */
        auto size() const -> std::size_t {
            std::size_t cnt {};  // 计数器

            listNode<ValueType> * moving {root->next};  // 从第一个有效节点开始

            // 遍历链表，统计节点数量
            while (moving) {
                ++cnt;

                moving = moving->next;
            }

            return cnt;
        }

        /**
         * @brief 在链表尾部插入一个新节点
         * 
         * @param value_ 要插入的值
         */
        void insert(ValueType const & value_) {
            // 创建新节点并插入到链表尾部
            far->next = new listNode<ValueType> {value_, nullptr};

            far = far->next;  // 更新尾节点
        }

        /**
         * @brief 在指定索引位置插入一个新节点
         * 
         * @param index_ 插入位置的索引
         * @param value_ 要插入的值
         */
        void insert(std::size_t index_, ValueType const & value_) {
            locate(index_);  // 定位到指定索引的前一个节点

            // 创建新节点并插入到指定位置
            before->next = new listNode<ValueType> {value_, before->next};

            // 如果新节点插入到尾部，更新尾节点
            if (far->next) {
                far = far->next;
            }
        }

        /**
         * @brief 删除链表的最后一个节点
         */
        void remove() {
            locate(size());  // 定位到倒数第二个节点

            delete before->next;  // 删除最后一个节点

            before->next = nullptr;  // 更新倒数第二个节点的 next 指针
            far = before;  // 更新尾节点
        }

        /**
         * @brief 删除指定索引位置的节点
         * 
         * @param index_ 要删除节点的索引
         */
        void remove(std::size_t index_) {
            locate(index_);  // 定位到指定索引的前一个节点

            // 如果要删除的节点是尾节点，更新尾节点
            if (before->next == far) {
                far = before;
            }

            listNode<ValueType> * tmp {before->next};  // 保存要删除的节点
            before->next = tmp->next;  // 更新前一个节点的 next 指针

            delete tmp;  // 删除节点
        }

        /**
         * @brief 获取指定索引位置节点的值
         * 
         * @param index_ 节点的索引
         * @return ValueType const& 指定索引位置节点的值的常量引用
         */
        auto getValue(std::size_t index_) const -> ValueType const & {
            locate(index_);  // 定位到指定索引的前一个节点

            return before->next->value;  // 返回指定节点的值
        }

        /**
         * @brief 设置指定索引位置节点的值
         * 
         * @param index_ 节点的索引
         * @param value_ 要设置的值
         */
        void setValue(std::size_t index_, ValueType const & value_) {
            locate(index_);  // 定位到指定索引的前一个节点

            before->next->value = value_;  // 设置指定节点的值
        }

        /**
         * @brief 反转从 from_ 到 to_ 之间的节点
         * 
         * @param from_ 反转区间的起始索引
         * @param to_ 反转区间的结束索引
         */
        void reverse(std::size_t from_, std::size_t to_) {
            locate(from_);  // 定位到起始索引的前一个节点
            listNode<ValueType> * front = before;  // 保存起始索引的前一个节点
            listNode<ValueType> * from = before->next;  // 保存起始节点

            locate(to_);  // 定位到结束索引的前一个节点
            listNode<ValueType> * to = before->next;  // 保存结束节点
            listNode<ValueType> * back = to->next;  // 保存结束节点的下一个节点

            reversing(from, to)->next = back;  // 反转节点并连接后续节点
            front->next = to;  // 连接反转后的节点到链表
        }
    };
}