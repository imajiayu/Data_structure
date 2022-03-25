#include <iostream>
#include <string.h>
using namespace std;

class Stack {//顺序栈类
public:
	int* elem;//首地址
	int length;//当前元素个数
	int size;//大小
public:
	Stack(int n);//初始化栈的长度
	bool push(int i);//入栈
	int pop();//出栈
	void printStack();//遍历打印
};

Stack::Stack(int n) {//初始化函数，申请空间，将长度与容量置零
	elem = (int*)malloc(sizeof(int) * n);
	size = n;
	length = 0;
}

bool Stack::push(int i) {//入栈，栈已满则返回false
	if (length + 1 > size)
		return false;
	elem[length] = i;
	length++;
	return true;
}

int Stack::pop() {//出栈，返回出栈元素，栈空则返回零
	if (length == 0)
		return 0;
	length--;
	return elem[length];
}

void Stack::printStack() {//倒序遍历打印
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