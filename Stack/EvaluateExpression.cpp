#include <iostream>
#include <stack>
#include <math.h>
using namespace std;

bool In(char c) {//�ж��Ƿ�Ϊ�����
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '=')
		return true;
	else return false;
}

char Precede(char a, char b)//�Ƚ���������������ȼ�������ֵΪ< > =
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

int Operate(int a, char theta, int b) {//����һ����Ԫ������Ľ������������ֵ
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

int EvaluateExpression() {//���ʽ��ֵ
	stack<char> OPTR;//����������ջ
	stack<int> OPND;//��Ų�������ջ
	stack<char> singleNum;//�������㵥����������ֵ��ջ
	OPTR.push('=');
	char theta;
	int c;
	int a, b;
	c = getchar();
	while (c != '=' || OPTR.top() != '=') {
		if (!In(c)) {//����ǲ�����
			singleNum.push(c - '0');
			int cnt = 1;
			while (!In(c = getchar())) {//�������룬ֱ������һ�������
				singleNum.push(c - '0');
				cnt++;
			}
			int num = 0;
			for (int i = 0; i < cnt; i++) {//���������λ������ֵ
				num += singleNum.top() * pow(10, i);
				singleNum.pop();
			}
			OPND.push(num);//��������ջ
		}
		else switch (Precede(OPTR.top(), c)) {//�Ƚ���������ȼ�
		case '<'://ֱ����ջ
			OPTR.push(c);
			c = getchar();
			break;
		case '='://����������������ջ
			OPTR.pop();
			c = getchar();
			break;
		case '>'://����
			theta = OPTR.top();
			OPTR.pop();
			b = OPND.top();
			OPND.pop();
			a = OPND.top();
			OPND.pop();
			if (b == 0 && theta == '/')//�����ֳ�0���㣬�򷵻�
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
	if (result == -99999999)//����
		cout << "ERROR";
	else cout << result;
	return 0;
}