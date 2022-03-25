#include <iostream>
#include <string.h>
using namespace std;

class Queue {//循环队列类
public:
	int queueSize;//容量
	int length;//元素个数
	int* front;//指向队头
	int* rear;//指向队尾
	int* spaceFront;//指向分配空间的首地址
	int* spaceRear;//指向分配空间的末地址
public:
	Queue(int size);//初始化函数，容量为参数
	int dequeue();//出队
	bool enqueue(int elem);//入队
	void printQueue();//遍历打印
};

Queue::Queue(int size) {//队列的初始化
	queueSize = size;
	length = 0;
	spaceFront = spaceRear = front = rear = (int*)malloc(sizeof(int) * queueSize);
	for (int i = 0; i < queueSize - 1; i++)//定位指向分配空间末地址的指针
		spaceRear++;
}

bool Queue::enqueue(int elem) {//入队
	if (length == queueSize)//队满
		return false;
	*rear = elem;
	if (rear == spaceRear)//如果头指针指向分配空间末地址，则跳转至分配空间的首地址
		rear = spaceFront;
	else rear++;//否则直接向上移动一位
	length++;
	return true;
}

int Queue::dequeue() {//出队
	if (length == 0)//空队
		return -1;
	int result = *front;
	if (front == spaceRear)//如果尾指针指向分配空间末地址，则跳转至分配空间的首地址
		front = spaceFront;
	else front++;//否则直接向上移动一位
	length--;
	return result;
}

void Queue::printQueue() {
	int* cur = front;
	for (int i = 0; i < length; i++) {
		cout << *cur << ' ';
		if (cur == spaceRear)//如果当前指针指向分配空间末地址，则跳转至分配空间的首地址
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