#include<iostream>
using namespace std;

class LNode {		//�ڵ�
public:
	int data;
	LNode* next;
public:
	LNode();
};

LNode::LNode() {	//�ڵ��ʼ��
	data = 0;
	this->next = NULL;
}

class Llist {		//����ͷ���Ԫ�ش��泤��
public:
	LNode* head;
public:
	Llist();//��ʼ��
	void printList();//��ӡ����������Ԫ��
	bool insert(int i, int x);//���룬iΪλ�ã�xΪԪ��
	bool remove(int j);//�Ƴ���jΪλ��
	int check(int y);//���Ҳ�����λ��
	void uniqueList();//ȥ��
	bool reverse(int begin, int end);//���ã�begin��endΪ��ʼλ��
};

Llist::Llist() { //��ͷ�ڵ����洢�ռ䣬������0��nextָ��ΪNULL
	this->head = (LNode*)malloc(sizeof(LNode));
	this->head->data = 0;
	this->head->next = NULL;
}

void Llist::printList() { //��������ӡ
	LNode* temp = this->head;
	for (int i = 0; i < this->head->data; i++) {
		temp = temp->next;
		cout << temp->data << ' ';
	}
	cout << endl;
}

bool Llist::insert(int i, int x) { //����
	if (i<1 || i>this->head->data + 1) //λ�úϷ����ж�
		return false;
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (!newNode)
		return false;
	LNode* temp = this->head;
	for (int t = 0; t < i - 1; t++) //��ָ���ƶ�����Ҫ����λ�õ�ǰһ���ڵ�
		temp = temp->next;
	newNode->next = temp->next; //����
	temp->next = newNode;
	newNode->data = x;
	this->head->data++; //���ȼ�1
	return true;
}

bool Llist::remove(int j) {
	if (j<1 || j>this->head->data) //λ�úϷ����ж�
		return false;
	LNode* temp = this->head;
	for (int t = 0; t < j - 1; t++) //��ָ���ƶ�����Ҫɾ��λ�õ�ǰһ���ڵ�
		temp = temp->next;
	temp->next = temp->next->next; //ɾ��
	this->head->data--;//���ȼ�1
	return true;
}

int Llist::check(int y) { //����������
	LNode* temp = this->head;
	for (int i = 0; i < this->head->data; i++) {
		temp = temp->next;
		if (temp->data == y)
			return i + 1;
	}
	return -1;
}

void Llist::uniqueList() { //ȥ��
	LNode* cur = this->head->next;
	LNode* pre = NULL;
	LNode* next = NULL;
	while (cur != NULL) {
		pre = cur;
		next = cur->next;
		while (next != NULL) {
			if (cur->data == next->data) {//���ҵ��ظ�Ԫ�أ�����ɾ��
				pre->next = next->next;
				this->head->data--;
			}
			else pre = next;//�������¶�λpreָ��
			next = next->next;
		}
		cur = cur->next;
	}
}

bool Llist::reverse(int begin, int end) {//����
	if (begin >= end)
		return false;
	if (begin<1 || begin>this->head->data - 1)
		return false;
	if (end<2 || end>this->head->data)//����Ϸ����ж�
		return false;
	int count = end - begin;
	LNode* pre = this->head;
	for (int i = 0; i < begin - 1; i++)//��λpreָ�뵽��Ҫ���õ��׸�Ԫ�ص�ǰһ���ڵ�
		pre = pre->next;
	LNode* next = pre;//��λnextָ�뵽��Ҫ���õ����һ��Ԫ�ص���һ���ڵ�
	for (int i = 0; i < end - begin + 2; i++)
		next = next->next;
	LNode* top = pre->next;//topָ��ָ����Ҫ���õ��׸�Ԫ��
	LNode* cur = top;
	for (++count; count; count--) {//��ʼ����
		for (int i = 0; i < count - 1; i++)
			cur = cur->next;
		pre->next = cur;
		pre = pre->next;
		cur = top;
	}
	pre->next = next;
	return true;
}

int main() {
	Llist L;
	int count = 0;
	cin >> count;
	for (int i = 0; i < count; i++) {
		int temp;
		cin >> temp;
		L.insert(1, temp);
	}
	int i, x;
	cin >> i >> x;
	L.insert(i, x);
	L.printList();
	int j;
	cin >> j;
	L.remove(j);
	L.printList();
	int y;
	cin >> y;
	cout << L.check(y) << endl;
	cout << L.head->data;
	return 0;
}