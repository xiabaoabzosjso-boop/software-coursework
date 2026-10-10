#include <iostream>
using namespace std;

typedef int ElemType;
typedef struct node {
	ElemType data;
	struct node* next;
}Lnode;

class LinkList
{
private:
	Lnode* head;
	int length;

public:
	LinkList() :head(nullptr), length(0) {};//初始化

	//重制列表
	void freeLinkList()
	{
		Lnode* current = head;
		while (current != nullptr)
		{
			Lnode* temp = current->next;
			delete current;
			current = temp;
		}
		head = nullptr;
		length = 0;
	}

	//销毁列表
	~LinkList() {
		freeLinkList();
	}

	//1.尾插法
	void append_tail(int val);

	//2.头插法
	void append_head(int val);

	//链表长度
	int Length();

	//3.手动赋值
	void fillLinkList();

	//4.查找元素
	ElemType Find_elem_val(int pos);

	//5.查找元素2
	ElemType Find_elem_pos(int val);

	//求前驱
	ElemType Pre_List(int val);

	//求houji
	ElemType Next_List(int val);

	//6.在指定位置插入元素
	void InsertLinkList(int val, int pos);

	//7.指定删除某个元素
	void DeleteelemLinkList(int val);

	void DeleteLinkListByPos(int pos);

	//8.排序
	void SortLinkList(LinkList& L);

	//实现单链表的逆序存放
	void ReverseList(LinkList& L);
};

void LinkList::append_tail(int val)
{
	Lnode* current = new Lnode;
	current->data = val;
	current->next = nullptr;

	if (head == nullptr)
	{
		head = current;
	}
	else
	{
		Lnode* temp = head;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = current;
	}
	length++;
}

void LinkList::append_head(int val)
{
	Lnode* current = new Lnode;
	current->data = val;
	current->next = head;
	head = current;
	length++;
}

int LinkList::Length()
{
	return length;
}

void LinkList::fillLinkList()
{
	int n;
	cin >> n;

	if (!cin || n < 0)
	{
		return;
	}

	freeLinkList();

	for (int i = 0; i < n; i++)
	{
		ElemType x;
		cin >> x;

		if (!cin)
		{
			return;
		}

		append_tail(x);
	}
}

ElemType LinkList::Find_elem_val(int pos)
{
	if (pos < 1 || pos > length)
	{
		return -1;
	}

	Lnode* current = head;
	for (int i = 1; i < pos; i++)
	{
		current = current->next;
	}
	return current->data;
}

ElemType LinkList::Find_elem_pos(int val)
{
	Lnode* current = head;
	int pos = 1;

	while (current != nullptr)
	{
		if (current->data == val)
		{
			return pos;
		}
		current = current->next;
		pos++;
	}
	return 0;
}

ElemType LinkList::Pre_List(int val)
{
	Lnode* previous = nullptr;
	Lnode* current = head;

	while (current != nullptr)
	{
		if (current->data == val)
		{
			if (previous == nullptr)
			{
				return -1;
			}
			return previous->data;
		}
		previous = current;
		current = current->next;
	}
	return -1;
}

ElemType LinkList::Next_List(int val)
{
	Lnode* current = head;

	while (current != nullptr)
	{
		if (current->data == val)
		{
			if (current->next == nullptr)
			{
				return -1;
			}
			return current->next->data;
		}
		current = current->next;
	}
	return -1;
}

void LinkList::InsertLinkList(int val, int pos)
{
	if (pos < 1 || pos > length + 1)
	{
		return;
	}

	if (pos == 1)
	{
		append_head(val);
		return;
	}

	Lnode* temp = head;
	for (int i = 1; i < pos - 1; i++)
	{
		temp = temp->next;
	}

	Lnode* current = new Lnode;
	current->data = val;
	current->next = temp->next;
	temp->next = current;
	length++;
}

void LinkList::DeleteelemLinkList(int val)
{
	while (head != nullptr && head->data == val)
	{
		Lnode* toDelete = head;
		head = head->next;
		delete toDelete;
		length--;
	}

	if (head == nullptr)
	{
		return;
	}

	Lnode* temp = head;
	while (temp->next != nullptr)
	{
		if (temp->next->data == val)
		{
			Lnode* toDelete = temp->next;
			temp->next = toDelete->next;
			delete toDelete;
			length--;
		}
		else
		{
			temp = temp->next;
		}
	}
}

void LinkList::DeleteLinkListByPos(int pos)
{
	if (pos < 1 || pos > length)
	{
		return;
	}

	Lnode* toDelete;

	if (pos == 1)
	{
		toDelete = head;
		head = head->next;
	}
	else
	{
		Lnode* previous = head;
		for (int i = 1; i < pos - 1; i++)
		{
			previous = previous->next;
		}
		toDelete = previous->next;
		previous->next = toDelete->next;
	}

	delete toDelete;
	length--;
}

void LinkList::SortLinkList(LinkList& L)
{
	if (L.length < 2)
	{
		return;
	}

	for (int i = 0; i < L.length - 1; i++)
	{
		Lnode* current = L.head;
		bool swapped = false;

		for (int j = 0; j < L.length - i - 1; j++)
		{
			if (current->data > current->next->data)
			{
				ElemType temp = current->data;
				current->data = current->next->data;
				current->next->data = temp;
				swapped = true;
			}
			current = current->next;
		}

		if (!swapped)
		{
			break;
		}
	}
}

void LinkList::ReverseList(LinkList& L)
{
	Lnode* previous = nullptr;
	Lnode* current = L.head;

	while (current != nullptr)
	{
		Lnode* next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}

	L.head = previous;
}

int main()
{
	LinkList* L = nullptr;
	int choice;

	while (true)
	{
		cout << "\n========== 单链表操作菜单 ==========\n";
		cout << "1. 初始化或重置链表\n";
		cout << "2. 销毁链表\n";
		cout << "3. 清空链表\n";
		cout << "4. 链表长度\n";
		cout << "5. 指定位置的元素值\n";
		cout << "6. 链表已存在元素的位序\n";
		cout << "7. 求输入元素的直接前驱\n";
		cout << "8. 求输入元素的直接后继\n";
		cout << "9. 在第i个位置插入一个元素\n";
		cout << "10. 删除第i个元素\n";
		cout << "11. 输出所有的链表元素\n";
		cout << "12. 初始化并用头插法或尾插法输入元素\n";
		cout << "13. 实现单链表的逆序存放\n";
		cout << "14. 实现单链表的排序\n";
		cout << "0. 退出\n";
		cout << "请选择：";

		if (!(cin >> choice))
		{
			cout << "请输入整数！\n";
			break;
		}

		if (choice == 0)
			break;

		if (choice < 1 || choice > 14)
		{
			cout << "菜单编号错误！\n";
			continue;
		}

		if (L == nullptr &&
			choice != 1 && choice != 2 && choice != 12)
		{
			cout << "链表未初始化或已销毁，请先初始化！\n";
			continue;
		}

		int pos = 0;
		int val = 0;
		bool display = false;

		if (choice == 5 || choice == 9 || choice == 10)
		{
			cout << "请输入位置（从1开始）：";

			if (!(cin >> pos))
			{
				cout << "位置必须是整数！\n";
				break;
			}

			int upper = L->Length();
			if (choice == 9)
				upper++;

			if (pos < 1 || pos > upper)
			{
				if (upper == 0)
					cout << "链表为空！\n";
				else
					cout << "位置越界，有效范围为1到"
					<< upper << "！\n";

				continue;
			}
		}

		if (choice == 6 || choice == 7 ||
			choice == 8 || choice == 9)
		{
			cout << "请输入元素值：";

			if (!(cin >> val))
			{
				cout << "元素值必须是整数！\n";
				break;
			}
		}

		switch (choice)
		{
		case 1:
		{
			if (L == nullptr)
				L = new LinkList;
			else
				L->freeLinkList();

			cout << "链表已初始化或重置。\n";
			break;
		}

		case 2:
		{
			if (L == nullptr)
			{
				cout << "链表未初始化或已经销毁！\n";
			}
			else
			{
				delete L;
				L = nullptr;
				cout << "链表已销毁。\n";
			}
			break;
		}

		case 3:
		{
			L->freeLinkList();
			cout << "链表已清空。\n";
			break;
		}

		case 4:
		{
			cout << "链表长度为：" << L->Length() << '\n';
			break;
		}

		case 5:
		{
			cout << "第" << pos << "个元素为："
				<< L->Find_elem_val(pos) << '\n';
			break;
		}

		case 6:
		{
			int index = L->Find_elem_pos(val);

			if (index == 0)
				cout << "该元素不存在！\n";
			else
				cout << "该元素首次出现的位序为："
				<< index << '\n';

			break;
		}

		case 7:
		{
			int index = L->Find_elem_pos(val);

			if (index == 0)
				cout << "该元素不存在，无法求前驱！\n";
			else if (index == 1)
				cout << "第一个元素没有直接前驱！\n";
			else
				cout << "直接前驱为："
				<< L->Pre_List(val) << '\n';

			break;
		}

		case 8:
		{
			int index = L->Find_elem_pos(val);

			if (index == 0)
				cout << "该元素不存在，无法求后继！\n";
			else if (index == L->Length())
				cout << "最后一个元素没有直接后继！\n";
			else
				cout << "直接后继为："
				<< L->Next_List(val) << '\n';

			break;
		}

		case 9:
		{
			L->InsertLinkList(val, pos);
			cout << "插入成功。\n";
			break;
		}

		case 10:
		{
			ElemType deletedValue = L->Find_elem_val(pos);
			L->DeleteLinkListByPos(pos);

			cout << "删除成功，删除的元素为："
				<< deletedValue << '\n';
			break;
		}

		case 11:
		{
			display = true;
			break;
		}

		case 12:
		{
			int n;
			int method;

			cout << "请输入元素个数：";

			if (!(cin >> n))
			{
				cout << "元素个数必须是整数！\n";
				break;
			}

			if (n < 0)
			{
				cout << "元素个数不能为负数！\n";
				break;
			}

			cout << "请选择：1.头插法  2.尾插法：";

			if (!(cin >> method))
			{
				cout << "请输入整数！\n";
				break;
			}

			if (method != 1 && method != 2)
			{
				cout << "只能选择1或2！\n";
				break;
			}

			if (L == nullptr)
				L = new LinkList;
			else
				L->freeLinkList();

			if (n > 0)
				cout << "请输入" << n << "个整数：\n";

			for (int i = 0; i < n; i++)
			{
				ElemType value;

				if (!(cin >> value))
				{
					cout << "元素值必须是整数！\n";
					break;
				}

				if (method == 1)
					L->append_head(value);
				else
					L->append_tail(value);
			}

			if (cin)
			{
				cout << "链表建立完成。\n";
				display = true;
			}
			break;
		}

		case 13:
		{
			if (L->Length() == 0)
			{
				cout << "链表为空！\n";
			}
			else
			{
				L->ReverseList(*L);
				cout << "逆序完成。\n";
				display = true;
			}
			break;
		}

		case 14:
		{
			if (L->Length() == 0)
			{
				cout << "链表为空！\n";
			}
			else
			{
				L->SortLinkList(*L);
				cout << "升序排序完成。\n";
				display = true;
			}
			break;
		}
		}

		if (!cin)
			break;

		if (display)
		{
			int n = L->Length();

			if (n == 0)
			{
				cout << "链表为空！\n";
			}
			else
			{
				cout << "当前链表：";
				for (int i = 1; i <= n; i++)
				{
					cout << L->Find_elem_val(i);
					if (i < n)
						cout << ' ';
				}
				cout << '\n';
			}
		}
	}

	delete L;
	cout << "程序已退出。\n";
	return 0;
}