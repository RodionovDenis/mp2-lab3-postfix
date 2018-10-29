#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <iostream>
#include <string>
#include <vector>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	double *value; //для хранения значений переменных выражения
public:
	TPostfix(string _infix);
	string GetInfix();
	string GetPostfix();
	void ChangeInfix(string _infix);
	bool IsCorrect(); //проверка на корректность выражения
	void ToPostfix(); // получение постфикса
	void ReadArguments(); //ввод значений переменных
	double Calculate(); // вычисление
};


#endif