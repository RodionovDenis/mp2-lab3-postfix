#include "postfix.h"
#include "stack.h"

using namespace std;

bool IsOperation(char elem);
int priority(char elem);
double result(double op1, double op2, char operat);
bool IsNumber(char elem);

TStack<char> stack_operation(MaxStackSize); // для преобразования в постфикс и проверки на корректность
TStack<string> stack_arguments(MaxStackSize); // для хранение аргументов
TStack<double> stack_value(MaxStackSize); //для хранения соответствующих значений
TStack<double> stack_value_postfix(MaxStackSize); //для высчитывания результата

TPostfix::TPostfix(string _infix) : infix(_infix), postfix(""), value(nullptr) {}
string TPostfix:: GetInfix()
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
	stack_operation.clear();
	if (IsOperation(infix[0]) || IsOperation(infix[infix.size() - 1]))//выражение не начинается и не заканчивается операцией
		return false;
	for (int i = 1; i < infix.size() - 1; i++) // в выражении нет двух операций подряд
		if (IsOperation(infix[i]) && IsOperation(infix[i + 1]))
			return false;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			stack_operation.push(1);
		if (infix[i] == ')')
		{
			if (stack_operation.IsEmpty())
				flag = 1;
			stack_operation.erase();
		}
	}
	if (flag)
		return false;
	return (stack_operation.IsEmpty()) ? true : false;
}
void TPostfix::ToPostfix() // получение постфикса
{
	stack_operation.clear();
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
				if (priority(infix[i]) == 0 || stack_operation.IsEmpty() || priority(infix[i]) > priority(stack_operation.pop_nd()))
					stack_operation.push(infix[i]);
				else
				{
					a = stack_operation.lenght();
					for (int j = 0; j < a; j++)
					{
						if (priority(stack_operation.pop_nd()) >= priority(infix[i]))
						{
							postfix += stack_operation.pop();
							postfix += ' ';
						}
						else
							break;
					}
					stack_operation.push(infix[i]);
				}
			}
			else
			{
				a = stack_operation.lenght();
				for (int j = 0; j < a; j++)
				{
					if (stack_operation.pop_nd() != '(')
					{
						postfix += stack_operation.pop();
						postfix += ' ';
					}
					else
					{
						stack_operation.erase();
						break;
					}
				}
			}
		}
	}
	a = stack_operation.lenght();
	for (int j = 0; j < a; j++)
	{
		postfix += stack_operation.pop();
		if (j != a - 1)
			postfix += ' ';
	}
}
void TPostfix::ReadArguments() //ввод значений переменных
{
	stack_arguments.clear();
	stack_value.clear();
	string ss;
	for (int i = infix.size() - 1; i >= 0; i--)
		if (!IsOperation(infix[i]) && !IsNumber(infix[i]) && infix[i] != '.')
		{
			ss += infix[i];
			if (i != 0 && !IsOperation(infix[i - 1]) && !IsNumber(infix[i - 1]))
				continue;
			reverse(ss.begin(), ss.end());
			stack_arguments.push(ss);
			ss.clear();
		}
	int res = stack_arguments.lenght();
	value = new double[res];
	if (res)
		cout << "Введите значения переменных." << endl;
	for (int i = 0; i < res; i++)
	{
		cout << stack_arguments.pop() << "=";
		cin >> value[i];
	}
	for (int i = res - 1; i >= 0; i--)
		stack_value.push(value[i]);
}
double TPostfix::Calculate() // вычисление
{
	stack_value_postfix.clear();
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
				stack_value_postfix.push(stack_value.pop());
			}
			else if (IsNumber(postfix[i]) || postfix[i] == '.')
			{
				ss += postfix[i];
				if (i != postfix.size() - 1 && IsNumber(postfix[i + 1]))
					continue;
				if (postfix[i + 1] == '.')
					continue;
				tmp = stod(ss);
				stack_value_postfix.push(tmp);
				ss.clear();
			}
			else
			{
				tmp = result(stack_value_postfix.pop(), stack_value_postfix.pop(), postfix[i]);
				stack_value_postfix.push(tmp);
			}
		}
		else continue;
	}
	return stack_value_postfix.pop();
}

bool IsOperation(char elem)
{
	return (elem == '(' || elem == ')' || elem == '+' || elem == '-' || elem == '*' || elem == '/') ? true : false;
}

int priority(char elem)
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

double result(double op1, double op2, char operat)
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
