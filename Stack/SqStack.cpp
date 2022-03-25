#include <iostream>
#include <string.h>
using namespace std;

class Stack {//˳��ջ��
public:
	int* elem;//�׵�ַ
	int length;//��ǰԪ�ظ���
	int size;//��С
public:
	Stack(int n);//��ʼ��ջ�ĳ���
	bool push(int i);//��ջ
	int pop();//��ջ
	void printStack();//������ӡ
};

Stack::Stack(int n) {//��ʼ������������ռ䣬����������������
	elem = (int*)malloc(sizeof(int) * n);
	size = n;
	length = 0;
}

bool Stack::push(int i) {//��ջ��ջ�����򷵻�false
	if (length + 1 > size)
		return false;
	elem[length] = i;
	length++;
	return true;
}

int Stack::pop() {//��ջ�����س�ջԪ�أ�ջ���򷵻���
	if (length == 0)
		return 0;
	length--;
	return elem[length];
}

void Stack::printStack() {//���������ӡ
	for (int i = length-1; i!=-1; i--)
		cout << elem[i]<<' ';
}

int main() {
	int n;
	cin >> n;
	Stack S(n);
	while (true) {
		char cmd[20];
		cin >> cmd;
		if (!strcmp(cmd, "pop")) {
			int result = S.pop();
			if (!result)
				cout << "Stack is Empty" << endl;
			else cout << result << endl;
		}
		if (!strcmp(cmd, "push")) {
			int temp;
			cin >> temp;
			if (!S.push(temp))
				cout << "Stack is Full" << endl;
		}
		if (!strcmp(cmd, "quit")) {
			S.printStack();
			return 0;
		}
	}
}