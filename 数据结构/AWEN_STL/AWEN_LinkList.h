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
        //删除节点函数
        void erase_node(NodeBase* node) noexcept
        {
            assert(node != &sentinel_);

            NodeBase* previous = node->prev;
            NodeBase* next_node = node->next;

            previous->next = next_node;
            next_node->prev = previous;

            delete static_cast<Node*>(node);
            --size_;
        }
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
        T& front() noexcept
        {
            assert(!empty());
            return static_cast<Node*>(sentinel_.next)->data;
        }

        const T& front() const noexcept
        {
            assert(!empty());
            return static_cast<const Node*>(sentinel_.next)->data;
        }

        T& back() noexcept
        {
            assert(!empty());
            return static_cast<Node*>(sentinel_.prev)->data;
        }

        const T& back() const noexcept
        {
            assert(!empty());
            return static_cast<const Node*>(sentinel_.prev)->data;
        }
        void push_front(const T& value)
        {
            Node* new_node = new Node(value);
            NodeBase* old_head = sentinel_.next;

            new_node->prev = &sentinel_;
            new_node->next = old_head;

            old_head->prev = new_node;
            sentinel_.next = new_node;

            ++size_;
        }

        void pop_front() noexcept
        {
            assert(!empty());
            erase_node(sentinel_.next);
        }

        void pop_back() noexcept
        {
            assert(!empty());
            erase_node(sentinel_.prev);
        }
    };
}

#endif // MY_LINKLIST_H