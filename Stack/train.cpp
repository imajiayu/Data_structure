#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <iostream>
using namespace std;

bool dispatching(stack<char> entry, char* queue) {//ģ���վ���� entryΪ���ڴ��Ѿ��źõ�ջ��queueΪ��Ҫ�ж��Ƿ���е�˳��
	stack<char> station;//��վ
	int i = 0;
	while (true) {
		if (entry.empty() && station.empty())//��վ����ڶ��գ�������
			return true;
		if (entry.empty() && station.top() != queue[i])//��ڿգ��ҳ�վջ��Ԫ�ز�����queue��ǰԪ�أ�������
			return false;
		if (!entry.empty()) {
			if (entry.top() != queue[i] && station.empty()) {//������ջ��Ԫ����ջ����վ
				station.push(entry.top());
				entry.pop();
			}
			else if (entry.top() != queue[i] && station.top() != queue[i]) {//������ջ��Ԫ����ջ����վ
				station.push(entry.top());
				entry.pop();
			}
			else if (entry.top() == queue[i]) {//����վ
				entry.pop();
				i++;
			}
			else if (station.top() == queue[i]) {//����վ
				station.pop();
				i++;
			}
		}
		else if (entry.empty())
			if (station.top() == queue[i]) {
				station.pop();
				i++;
			}
	}
}

int initDeque(stack<char>& init) {
	stack<char> temp;
	char c;
	int cnt = 0;
	while ((c = getchar()) != '\n') {
		temp.push(c);
		cnt++;
	}
	while (!temp.empty()) {
		init.push(temp.top());
		temp.pop();
	}
	return cnt;
}

int main() {
	stack<char> deque;
	int num = initDeque(deque);
	while (true) {
		char temp[10000];
		if (EOF == scanf("%s", temp))
			break;
		if (dispatching(deque, temp, num))
			cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}