#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T *pMem;
	int size;
	int top;
public:
	TStack(int _size = MaxStackSize)
	{
		if ((_size < 1) || (_size > MaxStackSize))
			throw "data is not correct";
		size = _size;
		top = -1;
		pMem = new T[size];
	}
	~TStack()
	{
		delete[] pMem;
	}
	bool IsEmpty()
	{
		return top == -1;
	}
	bool IsFull()
	{
		return top == size - 1;
	}
	void Clear()//очистить
	{
		top = -1;
	}
	void Erase()//удалить последний
	{
		if (!IsEmpty())
			top--;
	}
	T Pop()
	{
		return pMem[top--];
	}
	T PopWithoutDelete()//посмотреть без удаления
	{
		return pMem[top];
	}
	void Push(T v)
	{
		pMem[++top] = v;
	}
	int Length() //элементов в стэке в момент времени t.
	{
		return top + 1;
	}
};

#endif