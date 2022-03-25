#include <iostream>
#include <string.h>
using namespace std;

class Queue {//ѭ��������
public:
	int queueSize;//����
	int length;//Ԫ�ظ���
	int* front;//ָ���ͷ
	int* rear;//ָ���β
	int* spaceFront;//ָ�����ռ���׵�ַ
	int* spaceRear;//ָ�����ռ��ĩ��ַ
public:
	Queue(int size);//��ʼ������������Ϊ����
	int dequeue();//����
	bool enqueue(int elem);//���
	void printQueue();//������ӡ
};

Queue::Queue(int size) {//���еĳ�ʼ��
	queueSize = size;
	length = 0;
	spaceFront = spaceRear = front = rear = (int*)malloc(sizeof(int) * queueSize);
	for (int i = 0; i < queueSize - 1; i++)//��λָ�����ռ�ĩ��ַ��ָ��
		spaceRear++;
}

bool Queue::enqueue(int elem) {//���
	if (length == queueSize)//����
		return false;
	*rear = elem;
	if (rear == spaceRear)//���ͷָ��ָ�����ռ�ĩ��ַ������ת������ռ���׵�ַ
		rear = spaceFront;
	else rear++;//����ֱ�������ƶ�һλ
	length++;
	return true;
}

int Queue::dequeue() {//����
	if (length == 0)//�ն�
		return -1;
	int result = *front;
	if (front == spaceRear)//���βָ��ָ�����ռ�ĩ��ַ������ת������ռ���׵�ַ
		front = spaceFront;
	else front++;//����ֱ�������ƶ�һλ
	length--;
	return result;
}

void Queue::printQueue() {
	int* cur = front;
	for (int i = 0; i < length; i++) {
		cout << *cur << ' ';
		if (cur == spaceRear)//�����ǰָ��ָ�����ռ�ĩ��ַ������ת������ռ���׵�ַ
			cur = spaceFront;
		else cur++;
	}
}

int main() {
	int size;
	cin >> size;
	Queue q(size);
	while (true) {
		char cmd[20];
		cin >> cmd;
		if (!strcmp(cmd, "dequeue")) {
			int result = q.dequeue();
			if (result == -1)
				cout << "Queue is Empty" << endl;
			else cout << result << endl;
		}
		if (!strcmp(cmd, "enqueue")) {
			int elem;
			cin >> elem;
			if (!q.enqueue(elem))
				cout << "Queue is Full" << endl;
		}
		if (!strcmp(cmd, "quit")) {
			q.printQueue();
			break;
		}
	}
	return 0;
}