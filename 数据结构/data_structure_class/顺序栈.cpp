#include <iostream>
using namespace std;

typedef int ElemType;

class Stack
{
private:
    ElemType* s;
    int top;
    int capacity;

public:
    Stack(int capacity)
        : s(new ElemType[capacity]), top(-1), capacity(capacity) {
    }

    ~Stack()
    {
        delete[] s;
    }

    void clear()
    {
        top = -1;
    }

    int length() const
    {
        return top + 1;
    }

    bool getTop(ElemType& value) const
    {
        if (top == -1)
            return false;

        value = s[top];
        return true;
    }

    bool push(ElemType value)
    {
        if (top == capacity - 1)
            return false;

        s[++top] = value;
        return true;
    }

    bool pop(ElemType& value)
    {
        if (top == -1)
            return false;

        value = s[top--];
        return true;
    }

    void show() const
    {
        for (int i = 0; i <= top; ++i)
            cout << s[i] << " ";
    }
};

int main()
{
    Stack* st = nullptr;
    int choice;
    ElemType value;

    while (true)
    {
        cout << "\n========== 顺序栈操作菜单 ==========\n";
        cout << "1. 创建或重置栈\n";
        cout << "2. 销毁栈\n";
        cout << "3. 清空栈\n";
        cout << "4. 查看栈长度\n";
        cout << "5. 查看栈顶元素\n";
        cout << "6. 入栈\n";
        cout << "7. 出栈\n";
        cout << "8. 显示栈\n";
        cout << "0. 退出\n";
        cout << "请选择：";

        if (!(cin >> choice))
        {
            cout << "输入错误，程序结束。\n";
            break;
        }

        if (choice == 0)
            break;

        if (choice < 1 || choice > 8)
        {
            cout << "菜单编号错误！\n";
            continue;
        }

        if (st == nullptr && choice != 1 && choice != 2)
        {
            cout << "请先输入1创建栈！\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            if (st == nullptr)
            {
                int capacity;
                cout << "请输入栈的容量：";

                if (!(cin >> capacity))
                {
                    cout << "容量必须是整数！\n";
                    break;
                }

                if (capacity <= 0)
                {
                    cout << "容量必须大于0！\n";
                    break;
                }

                st = new Stack(capacity);
                cout << "栈已创建。\n";
            }
            else
            {
                st->clear();
                cout << "栈已重置，容量保持不变。\n";
            }
            break;
        }

        case 2:
        {
            if (st == nullptr)
            {
                cout << "栈尚未创建或已经销毁！\n";
            }
            else
            {
                delete st;
                st = nullptr;
                cout << "栈已销毁。\n";
            }
            break;
        }

        case 3:
        {
            st->clear();
            cout << "栈已清空。\n";
            break;
        }

        case 4:
        {
            cout << "栈的长度为：" << st->length() << '\n';
            break;
        }

        case 5:
        {
            if (st->getTop(value))
                cout << "栈顶元素为：" << value << '\n';
            else
                cout << "栈为空！\n";

            break;
        }

        case 6:
        {
            cout << "请输入要入栈的整数：";

            if (!(cin >> value))
            {
                cout << "元素必须是整数！\n";
                break;
            }

            if (st->push(value))
                cout << "入栈成功。\n";
            else
                cout << "栈已满，入栈失败！\n";

            break;
        }

        case 7:
        {
            if (st->pop(value))
                cout << "出栈成功，元素为：" << value << '\n';
            else
                cout << "栈为空，出栈失败！\n";

            break;
        }

        case 8:
        {
            if (st->length() == 0)
            {
                cout << "栈为空！\n";
            }
            else
            {
                cout << "当前栈（从栈底到栈顶）：";
                st->show();
                cout << '\n';
            }
            break;
        }
        }

        if (!cin)
            break;
    }

    delete st;
    cout << "程序已退出。\n";
    return 0;
}