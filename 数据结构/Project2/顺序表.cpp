#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

typedef int ElemType;

class SqList {
private:
	ElemType* data;
	int length;
	int listsize;
public:
	bool InitSqList(SqList& s);
	void DeleteSqList(SqList& s);
	void ClearSqList(SqList& s);
	bool IsemptySqList(SqList& s);
	int LengthSqList(SqList& s);
	ElemType& GetelemSqList(SqList& s, int pos);
	int GetposSqList(SqList& s, ElemType n);
	bool IsInSqList(SqList& s, ElemType n);
	ElemType& PreSqList(SqList& s, ElemType n);
	ElemType& NextSqList(SqList& s, ElemType n);
	bool InsertSqList(SqList& s, int pos, ElemType n);
	bool DeleteElemSqList(SqList& s, int pos);
	bool DeleteElemSqList2(SqList& s, ElemType n);
	void SortSqList(SqList& s);
	void ShowSqList(SqList& s);
	SqList Merge(SqList& s1, SqList& s2);
};
bool SqList::InitSqList(SqList& s)
{
	s.data = new int[s.listsize];
	if (!s.data)
		exit(-1);
	s.length = 0;
	return true;
}
void SqList::DeleteSqList(SqList& s)
{
	delete[] s.data;
	s.data = nullptr;
	s.length = 0;
	s.listsize = 0;
}
void SqList::ClearSqList(SqList& s)
{
	s.length = 0;
}
bool SqList::IsemptySqList(SqList& s)
{
	return s.length == 0;
}
int SqList::LengthSqList(SqList& s)
{
	return s.length;
}
ElemType& SqList::GetelemSqList(SqList& s, int pos)
{
	return s.data[pos - 1];
}
int SqList::GetposSqList(SqList& s, ElemType n)
{
	for (int i = 0; i < s.length; i++)
	{
		if (s.data[i] == n)
		{
			return i;
		}
	}
	return -1;
}
bool SqList::IsInSqList(SqList& s, ElemType n)
{
	for (int i = 0; i < s.length; i++)
	{
		if (s.data[i] == n)
		{
			return true;
		}
	}
	return false;
}
ElemType& SqList::PreSqList(SqList& s, ElemType n)
{
	static ElemType dummy = -1;
	if (!s.IsInSqList(s, n)) return dummy;
	int pos = s.GetposSqList(s, n);
	if (pos == 0) return dummy;
	return s.data[pos - 1];
}
ElemType& SqList::NextSqList(SqList& s, ElemType n)
{
	static ElemType dummy = -1;
	if (!s.IsInSqList(s, n)) return dummy;
	int pos = s.GetposSqList(s, n);
	if (pos == s.length - 1) return dummy;
	return s.data[pos + 1];
}
bool SqList::InsertSqList(SqList& s, int pos, ElemType n)
{
	if (pos < 0 || pos > s.length) return false;
	if (s.length == s.listsize) return false;
	for (int i = s.length; i > pos; i--)
	{
		s.data[i] = s.data[i - 1];
	}
	s.data[pos] = n;
	s.length++;
	return true;
}
bool SqList::DeleteElemSqList(SqList& s, int pos)
{
	if (s.length == 0) return false;
	if (pos < 0 || pos >= s.length) return false;
	for (int i = pos; i < s.length - 1; i++)
	{
		s.data[i] = s.data[i + 1];
	}
	s.length--;
	return true;
}
bool SqList::DeleteElemSqList2(SqList& s, ElemType n)
{
	while (s.IsInSqList(s, n))
	{
		int pos = s.GetposSqList(s, n);
		s.DeleteElemSqList(s, pos);
	}
	return true;
}
void SqList::SortSqList(SqList& s)
{
	for (int i = 0; i < s.length - 1; i++)
	{
		for (int j = 0; j < s.length - i - 1; j++)
		{
			if (s.data[j] > s.data[j + 1])
			{
				ElemType x = s.data[j];
				s.data[j] = s.data[j + 1];
				s.data[j + 1] = x;
			}
		}
	}
}
void SqList::ShowSqList(SqList& s)
{
	for (int i = 0; i < s.length; i++)
	{
		cout << s.data[i] << " ";
	}
}
SqList SqList::Merge(SqList& s1, SqList& s2)
{
	s1.SortSqList(s1);
	s2.SortSqList(s2);
	SqList s;
	s.listsize = s1.listsize + s2.listsize;
	s.InitSqList(s);
	ElemType* p1 = s1.data;
	ElemType* p2 = s2.data;
	ElemType* p = s.data;
	ElemType* end1 = s1.data + s1.length;
	ElemType* end2 = s2.data + s2.length;
	while (p1 < end1 && p2 < end2)
	{
		if (*p1 < *p2)
		{
			*p++ = *p1++;
		}
		else
		{
			*p++ = *p2++;
		}
	}
	while (p1 < end1)
	{
		*p++ = *p1++;
	}
	while (p2 < end2)
	{
		*p++ = *p2++;
	}
	s.length = s1.length + s2.length;
	return s;
}


int main()
{
	int x;
	cout << "请输入一个数字:" << endl;
	cout << "1-----初始化一个线性表" << endl;
	cout << "2-----销毁线性表" << endl;
	cout << "3-----清空线性表" << endl;
	cout << "4-----判断线性表是否为空" << endl;
	cout << "5-----求线性表的长度" << endl;
	cout << "6-----获取线性表指定位置的元素" << endl;
	cout << "7-----获取线性表中元素的位置" << endl;
	cout << "8-----求前驱" << endl;
	cout << "9-----求后继" << endl;
	cout << "10----在线性表指定位置插入元素" << endl;
	cout << "11----删除线性表指定位置的元素" << endl;
	cout << "12----根据元素值，删除线性表中的元素" << endl;
	cout << "13----对线性表进行排序" << endl;
	cout << "14----显示线性表" << endl;
	cout << "15----合并两个非递减有序的线性表" << endl;
	cin >> x;
	switch(x) 
	{
	case 1:

	}
	return 0;
}