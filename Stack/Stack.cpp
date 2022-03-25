#include <iostream>
#include <string.h>
using namespace std;

class SNode {//栈的节点类
public:
	int data;
	SNode* next;
public:
	SNode();
	void assign();
};

SNode::SNode() {//节点初始化
	data = 0;
	next = (SNode*)malloc(sizeof(SNode));
	next = NULL;
}

void SNode::assign() {//给节点赋值
	cin >> this->data;
}

class Stack {//栈类
public:
	SNode* base;//栈底
	SNode* top;//栈顶
	int stackSize;//容量
	int size;//实际大小
public:
	Stack();//初始化
	void sizeInit();//给栈设置最大容量
	bool push();//入栈
	int pop();//出栈
	void printStack();//遍历打印
};

Stack::Stack() {
	top = base = (SNode*)malloc(sizeof(SNode));//栈底与栈顶均指向同一个节点
	size = 0;
	stackSize = 0;
}

void Stack::sizeInit() {
	cin >> this->stackSize;
}

bool Stack::push() {
	if (size == stackSize)//栈满
		return false;
	top->assign();
	SNode* newNode = (SNode*)malloc(sizeof(SNode));
	newNode->next = top;
	top = newNode;//top指针移动到新节点
	size++;
	return true;
}

int Stack::pop() {
	if (size == 0)
		return 0;
	int result = top->next->data;
	top = top->next;//top指针下移
	size--;
	return result;
}

void Stack::printStack() {//遍历打印
	SNode* cur = top->next;
	for (int i = 0; i < size; i++) {
		cout << cur->data << ' ';
		cur = cur->next;
	}
	cout << endl;
}

int main() {
	Stack S;
	S.sizeInit();
	while (true) {
		char cmd[20];
		cin >> cmd;
		if (!strcmp(cmd, "pop")) {
			int result = S.pop();
			if (!result)
				cout << "Stack is Empty" << endl;
			else cout << result << endl;
		}
		if (!strcmp(cmd, "push"))
			if (!S.push())
				cout << "Stack is Full" << endl;
		if (!strcmp(cmd, "quit")) {
			S.printStack();
			return 0;
		}
	}
}