#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	int a = 0;
	setlocale(LC_CTYPE, "Russian");
	string expression;
m:cout << "������� �������������� ���������(��� ��������)" << endl;
	cout << "��� ��������� ������� ����� ����������� '.' ��������: 5.2" << endl;
	cout << "����������� ������������� ����������, �������� ������������ � �� ���������� � �����. ������: res+sum" << endl;
	cin >> expression;
	TPostfix postfix(expression);
n:if (!postfix.IsCorrect())
{
	cout << "��������� �� ���������, ���������." << endl;
	goto m;
}
  postfix.ToPostfix();
k:postfix.ReadArguments();
  cout << "��������� ����������: " << postfix.Calculate() << endl;
  cout << "����������� �����: " << postfix.GetPostfix() << endl;
  cout << "�������� ����������� ��������:" << endl;
  cout << "1. ������ ������ �������������� ���������" << endl;
  cout << "2. ������ ������ �������� ����������(���� ��� ������������)" << endl;
  cout << "3. ����� �� ���������" << endl;
  cin >> a;
  switch (a)
  {
  case 1:
  {
	  cin >> expression;
	  postfix.ChangeInfix(expression);
	  goto n;
	  break;
  }
  case 2:
  {
	  goto k;
	  break;
  }
  case 3: break;
  }
  return 0;
}