#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

class TPostfix
{
private:
	string infix;
	string postfix;
	double *value; //��� �������� �������� ���������� ���������
	TStack<char> stackOperation; // ��� �������������� � �������� � �������� �� ������������
	TStack<string> stackArguments; // ��� �������� ����������
	TStack<double> stackValue; //��� �������� ��������������� ��������
	TStack<double> stackValuePostfix; //��� ������������ ����������

public:
	TPostfix(string _infix);
	string GetInfix();
	string GetPostfix();
	void ChangeInfix(string _infix);
	bool IsCorrect(); //�������� �� ������������ ���������
	void ToPostfix(); // ��������� ���������
	void ReadArguments(); //���� �������� ����������
	double Calculate(); // ����������
};


#endif