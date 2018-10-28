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
  TStack(int _size) 
  {
    if ((_size < 1) || (_size > MaxStackSize))
      throw "data is not correct";
	size = _size;
	top = -1;
    pMem = new T[size];
  }
  ~TStack()
  {
    delete [] pMem;
  }
  bool IsEmpty()
  {
	  return top == -1;
  }
  bool IsFull()
  {
	  return top == size - 1;
  }
  void clear()//очистить
  {
	  top = -1;
  }
  void erase()//удалить последний
  {
	  if (!IsEmpty())
		  top--;
  }
  T pop()      
  {
	  return pMem[top--];
  }
  T pop_nd()//посмотреть без удаления
  {
	  return pMem[top];
  }
  void push(T v) 
  {
	  pMem[++top] = v;
  }
  int lenght() //элементов в стэке в момент времени t.
  {
	  return top + 1;
  }
};

#endif
