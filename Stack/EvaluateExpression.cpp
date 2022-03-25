#include <iostream>
#include <stack>
#include <math.h>
using namespace std;

bool In(char c) {//判断是否为运算符
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
		return true;
	else return false;
}

char Precede(char a, char b)//比较两个运算符的优先级，返回值为< > =
{
	char result;
	if (a == '+' || a == '-')
	{
		if (b == '+' || b == '-' || b == ')' || b == '=')
			result = '>';
		else if (b == '*' || b == '/' || b == '(')
			result = '<';
	}
	else if (a == '*' || a == '/')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '=')
			result = '>';
		else if (b == '(')
			result = '<';
	}
	else if (a == '(')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
			result = '<';
		else if (b == ')')
			result = '=';
	}
	else if (a == ')')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '=')
			result = '>';
	}
	else if (a == '=')
	{
		if (b == '+' || b == '-' || b == '*' || b == '/' || b == '(')
			result = '<';
		else if (b == '=')
			result = '=';
	}
	return result;
}

int Operate(int a, char theta, int b) {//计算一个二元运算符的结果，并返回其值
	int result;
	if (theta == '+')
		result = a + b;
	else if (theta == '-')
		result = a - b;
	else if (theta == '*')
		result = a * b;
	else if (theta == '/')
		result = a / b;
	return result;
}

int EvaluateExpression() {//表达式求值
	stack<char> OPTR;//存放运算符的栈
	stack<int> OPND;//存放操作数的栈
	stack<char> singleNum;//用来计算单个操作数的值的栈
	OPTR.push('=');
	char theta;
	int c;
	int a, b;
	c = getchar();
	while (c != '=' || OPTR.top() != '=') {
		if (!In(c)) {//如果是操作数
			singleNum.push(c - '0');
			int cnt = 1;
			while (!In(c = getchar())) {//继续输入，直至输入一个运算符
				singleNum.push(c - '0');
				cnt++;
			}
			int num = 0;
			for (int i = 0; i < cnt; i++) {//计算这个多位数的数值
				num += singleNum.top() * pow(10, i);
				singleNum.pop();
			}
			OPND.push(num);//操作数入栈
		}
		else switch (Precede(OPTR.top(), c)) {//比较运算符优先级
		case '<'://直接入栈
			OPTR.push(c);
			c = getchar();
			break;
		case '='://左右括号相遇，出栈
			OPTR.pop();
			c = getchar();
			break;
		case '>'://计算
			theta = OPTR.top();
			OPTR.pop();
			b = OPND.top();
			OPND.pop();
			a = OPND.top();
			OPND.pop();
			if (b == 0 && theta == '/')//若出现除0运算，则返回
				return -99999999;
			OPND.push(Operate(a, theta, b));
			break;
		}
	}
	if (OPND.empty())
		return 0;
	else return OPND.top();
}

int main() {
	int result = EvaluateExpression();
	if (result == -99999999)//报错
		cout << "ERROR";
	else cout << result;
	return 0;
}