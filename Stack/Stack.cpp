#include <iostream>
#include <string.h>
using namespace std;

class SNode {//ջ�Ľڵ���
public:
	int data;
	SNode* next;
public:
	SNode();
	void assign();
};

SNode::SNode() {//�ڵ��ʼ��
	data = 0;
	next = (SNode*)malloc(sizeof(SNode));
	next = NULL;
}

void SNode::assign() {//���ڵ㸳ֵ
	cin >> this->data;
}

class Stack {//ջ��
public:
	SNode* base;//ջ��
	SNode* top;//ջ��
	int stackSize;//����
	int size;//ʵ�ʴ�С
public:
	Stack();//��ʼ��
	void sizeInit();//��ջ�����������
	bool push();//��ջ
	int pop();//��ջ
	void printStack();//������ӡ
};

Stack::Stack() {
	top = base = (SNode*)malloc(sizeof(SNode));//ջ����ջ����ָ��ͬһ���ڵ�
	size = 0;
	stackSize = 0;
}

void Stack::sizeInit() {
	cin >> this->stackSize;
}

bool Stack::push() {
	if (size == stackSize)//ջ��
		return false;
	top->assign();
	SNode* newNode = (SNode*)malloc(sizeof(SNode));
	newNode->next = top;
	top = newNode;//topָ���ƶ����½ڵ�
	size++;
	return true;
}

int Stack::pop() {
	if (size == 0)
		return 0;
	int result = top->next->data;
	top = top->next;//topָ������
	size--;
	return result;
}

void Stack::printStack() {//������ӡ
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