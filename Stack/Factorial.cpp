#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <iostream>
using namespace std;

class Data {//�����࣬������������뷵�ص�ַ
public:
	int n;//�������
	int* returnAddress;
public:
	Data() {//������
		n = 0;
		returnAddress = (int*)malloc(sizeof(int));
	}
	void setter(int n) {//�趨��ֵn��ֵ
		this->n = n;
	}
};

int factorial(int n) {//����ջģ��ݹ���׳�
	if (n == 0)//0�Ľ׳�Ϊ1��
		return 1;
	stack<Data> mystack;//ջ
	Data data;//�洢���ս����������
	data.setter(n);//��ʼ��
	while (data.n != 1) {//n=1��
		mystack.push(data);//��ʼ�ݹ�
		data.setter(data.n - 1);//��ջ
	}
	while (!mystack.empty()) {//ջ�գ�
		if (mystack.top().n == 1) {//��n=1ʱ��return1
			data.n = 1;
			mystack.pop();
		}
		else {
			data.n *= mystack.top().n;//����
			mystack.pop();
		}
	}
	return data.n;//end
}

int main() {
	cout << "Please enter the factorial you want:" << endl;
	int n;
	cin >> n;
	cout << "The result is:" << factorial(n);
	return 0;
}