#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <iostream>
using namespace std;

bool dispatching(stack<char> entry, char* queue) {//模拟出站函数 entry为出口处已经排好的栈，queue为需要判断是否可行的顺序
	stack<char> station;//车站
	int i = 0;
	while (true) {
		if (entry.empty() && station.empty())//车站和入口都空，即可行
			return true;
		if (entry.empty() && station.top() != queue[i])//入口空，且车站栈顶元素不等于queue当前元素，不可行
			return false;
		if (!entry.empty()) {
			if (entry.top() != queue[i] && station.empty()) {//将出口栈顶元素入栈至车站
				station.push(entry.top());
				entry.pop();
			}
			else if (entry.top() != queue[i] && station.top() != queue[i]) {//将出口栈顶元素入栈至车站
				station.push(entry.top());
				entry.pop();
			}
			else if (entry.top() == queue[i]) {//出车站
				entry.pop();
				i++;
			}
			else if (station.top() == queue[i]) {//出车站
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