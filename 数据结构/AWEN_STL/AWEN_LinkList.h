#ifndef MY_LINKLIST_H
#define MY_LINKLIST_H

#include <cstddef>

namespace AWEN
{
    template<typename T>
    class LinkList
    {
    private:
        // 基础节点：只负责连接
        struct NodeBase
        {
            NodeBase* prev = nullptr;
            NodeBase* next = nullptr;
        };

        // 元素节点：连接关系 + 元素值
        struct Node : public NodeBase
        {
            T data;
        };

        // 哨兵不保存元素，也不计入 size_
        NodeBase sentinel_;
        std::size_t size_ = 0;

    public:
        // 下一步添加构造函数
        LinkList() noexcept
        {
            sentinel_.prev = &sentinel_;
            sentinel_.next = &sentinel_;
        }

        // 后续实现深拷贝时再替换
        LinkList(const LinkList&) = delete;
        LinkList& operator=(const LinkList&) = delete;

        ~LinkList() noexcept{clear () }
        std::size_t size()noexcept
        {
            return size_;
        }
        bool empty()noexcept
        {
            return size_ == 0;
        }
        //尾插法
        void push_back(const T& value)
        {
            // 创建成功后，再修改链表连接
            Node* new_node = new Node(value);
            NodeBase* old_tail = sentinel_.prev;

            new_node->prev = old_tail;
            new_node->next = &sentinel_;

            old_tail->next = new_node;
            sentinel_.prev = new_node;

            ++size_;
        }
        void clear() noexcept
        {
            NodeBase* current = sentinel_.next;

            while (current != &sentinel_)
            {
                // 删除之前，保存下一个节点
                NodeBase* next_node = current->next;

                // 当前指针指向元素节点，转回实际类型后删除
                delete static_cast<Node*>(current);

                current = next_node;
            }

            // 恢复空环
            sentinel_.prev = &sentinel_;
            sentinel_.next = &sentinel_;
            size_ = 0;
        }
    };
}

#endif // MY_LINKLIST_H