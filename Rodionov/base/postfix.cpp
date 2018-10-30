#include "postfix.h"
#include "stack.h"

using namespace std;

bool IsOperation(char elem);
bool IsOperationForCorrect(char elem);
int Priority(char elem);
double Result(double op1, double op2, char operat);
bool IsNumber(char elem);

TPostfix::TPostfix(string _infix) : infix(_infix), postfix(""), value(nullptr) {}
string TPostfix::GetInfix()
{
	return infix;
}
string TPostfix::GetPostfix()
{
	return postfix;
}
void TPostfix::ChangeInfix(string _infix)
{
	infix = _infix;
	postfix.clear();
}
bool TPostfix::IsCorrect() //проверка на корректность выражения
{
	int flag = 0;
	stack_operation.Clear();
	if (IsOperationForCorrect(infix[0]) || IsOperationForCorrect(infix[infix.size() - 1]))//выражение не начинается и не заканчивается операцией
		return false;
	for (int i = 1; i < infix.size() - 1; i++) // в выражении нет двух операций подряд
		if (IsOperationForCorrect(infix[i]) && IsOperationForCorrect(infix[i + 1]))
			return false;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			stack_operation.Push(1);
		if (infix[i] == ')')
		{
			if (stack_operation.IsEmpty())
				flag = 1;
			stack_operation.Erase();
		}
	}
	if (flag)
		return false;
	return (stack_operation.IsEmpty()) ? true : false;
}
void TPostfix::ToPostfix() // получение постфикса
{
	stack_operation.Clear();
	int a = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (!IsOperation(infix[i]))
		{
			postfix += infix[i];
			if (i == infix.size() - 1 || IsOperation(infix[i + 1]))
				postfix += ' ';
		}
		else
		{
			if (infix[i] != ')')
			{
				if (Priority(infix[i]) == 0 || stack_operation.IsEmpty() || Priority(infix[i]) > Priority(stack_operation.PopWithoutDelete()))
					stack_operation.Push(infix[i]);
				else
				{
					a = stack_operation.Length();
					for (int j = 0; j < a; j++)
					{
						if (Priority(stack_operation.PopWithoutDelete()) >= Priority(infix[i]))
						{
							postfix += stack_operation.Pop();
							postfix += ' ';
						}
						else
							break;
					}
					stack_operation.Push(infix[i]);
				}
			}
			else
			{
				a = stack_operation.Length();
				for (int j = 0; j < a; j++)
				{
					if (stack_operation.PopWithoutDelete() != '(')
					{
						postfix += stack_operation.Pop();
						postfix += ' ';
					}
					else
					{
						stack_operation.Erase();
						break;
					}
				}
			}
		}
	}
	a = stack_operation.Length();
	for (int j = 0; j < a; j++)
	{
		postfix += stack_operation.Pop();
		if (j != a - 1)
			postfix += ' ';
	}
}
void TPostfix::ReadArguments() //ввод значений переменных
{
	stack_arguments.Clear();
	stack_value.Clear();
	string ss;
	for (int i = infix.size() - 1; i >= 0; i--)
		if (!IsOperation(infix[i]) && !IsNumber(infix[i]) && infix[i] != '.')
		{
			ss += infix[i];
			if (i != 0 && !IsOperation(infix[i - 1]) && !IsNumber(infix[i - 1]))
				continue;
			reverse(ss.begin(), ss.end());
			stack_arguments.Push(ss);
			ss.clear();
		}
	int res = stack_arguments.Length();
	value = new double[res];
	if (res)
		cout << "Введите значения переменных." << endl;
	for (int i = 0; i < res; i++)
	{
		cout << stack_arguments.Pop() << "=";
		cin >> value[i];
	}
	for (int i = res - 1; i >= 0; i--)
		stack_value.Push(value[i]);
}
double TPostfix::Calculate() // вычисление
{
	stack_value_postfix.Clear();
	double tmp = 0;
	string ss;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] != ' ')
		{
			if (!IsOperation(postfix[i]) && !IsNumber(postfix[i]) && postfix[i] != '.')
			{
				if (i != postfix.size() - 1 && postfix[i + 1] != ' ')
					continue;
				stack_value_postfix.Push(stack_value.Pop());
			}
			else if (IsNumber(postfix[i]) || postfix[i] == '.')
			{
				ss += postfix[i];
				if (i != postfix.size() - 1 && IsNumber(postfix[i + 1]))
					continue;
				if (postfix[i + 1] == '.')
					continue;
				tmp = stod(ss);
				stack_value_postfix.Push(tmp);
				ss.clear();
			}
			else
			{
				tmp = Result(stack_value_postfix.Pop(), stack_value_postfix.Pop(), postfix[i]);
				stack_value_postfix.Push(tmp);
			}
		}
		else continue;
	}
	return stack_value_postfix.Pop();
}

bool IsOperation(char elem)
{
	return (elem == '(' || elem == ')' || elem == '+' || elem == '-' || elem == '*' || elem == '/') ? true : false;
}

bool IsOperationForCorrect(char elem)
{
	return (elem == '+' || elem == '-' || elem == '*' || elem == '/') ? true : false;
}

int Priority(char elem)
{
	if (!IsOperation(elem))
		throw "data is not correct";
	if (elem == '(')
		return 0;
	else if (elem == ')')
		return 1;
	else if (elem == '+' || elem == '-')
		return 2;
	return 3;
}

double Result(double op1, double op2, char operat)
{
	if (operat == '+')
		return op1 + op2;
	else if (operat == '-')
		return op1 - op2;
	else if (operat == '*')
		return op1 * op2;
	else
		return op1 / op2;
}

bool IsNumber(char elem)
{
	for (char i = '0'; i <= '9'; i++)
		if (elem == i)
			return true;
	return false;
}