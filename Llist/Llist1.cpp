#include<iostream>
using namespace std;

class LNode {		//节点
public:
	int data;
	LNode* next;
public:
	LNode();
};

LNode::LNode() {	//节点初始化
	data = 0;
	this->next = NULL;
}

class Llist {		//链表，头结点元素储存长度
public:
	LNode* head;
public:
	Llist();//初始化
	void printList();//打印链表中所有元素
	bool insert(int i, int x);//插入，i为位置，x为元素
	bool remove(int j);//移除，j为位置
	int check(int y);//查找并返回位置
	void uniqueList();//去重
	bool reverse(int begin, int end);//逆置，begin与end为起始位置
};

Llist::Llist() { //给头节点分配存储空间，长度置0，next指针为NULL
	this->head = (LNode*)malloc(sizeof(LNode));
	this->head->data = 0;
	this->head->next = NULL;
}

void Llist::printList() { //遍历并打印
	LNode* temp = this->head;
	for (int i = 0; i < this->head->data; i++) {
		temp = temp->next;
		cout << temp->data << ' ';
	}
	cout << endl;
}

bool Llist::insert(int i, int x) { //插入
	if (i<1 || i>this->head->data + 1) //位置合法性判断
		return false;
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (!newNode)
		return false;
	LNode* temp = this->head;
	for (int t = 0; t < i - 1; t++) //将指针移动到需要插入位置的前一个节点
		temp = temp->next;
	newNode->next = temp->next; //插入
	temp->next = newNode;
	newNode->data = x;
	this->head->data++; //长度加1
	return true;
}

bool Llist::remove(int j) {
	if (j<1 || j>this->head->data) //位置合法性判断
		return false;
	LNode* temp = this->head;
	for (int t = 0; t < j - 1; t++) //将指针移动到需要删除位置的前一个节点
		temp = temp->next;
	temp->next = temp->next->next; //删除
	this->head->data--;//长度减1
	return true;
}

int Llist::check(int y) { //遍历并查找
	LNode* temp = this->head;
	for (int i = 0; i < this->head->data; i++) {
		temp = temp->next;
		if (temp->data == y)
			return i + 1;
	}
	return -1;
}

void Llist::uniqueList() { //去重
	LNode* cur = this->head->next;
	LNode* pre = NULL;
	LNode* next = NULL;
	while (cur != NULL) {
		pre = cur;
		next = cur->next;
		while (next != NULL) {
			if (cur->data == next->data) {//若找到重复元素，将其删除
				pre->next = next->next;
				this->head->data--;
			}
			else pre = next;//否则重新定位pre指针
			next = next->next;
		}
		cur = cur->next;
	}
}

bool Llist::reverse(int begin, int end) {//逆置
	if (begin >= end)
		return false;
	if (begin<1 || begin>this->head->data - 1)
		return false;
	if (end<2 || end>this->head->data)//输入合法性判断
		return false;
	int count = end - begin;
	LNode* pre = this->head;
	for (int i = 0; i < begin - 1; i++)//定位pre指针到需要逆置的首个元素的前一个节点
		pre = pre->next;
	LNode* next = pre;//定位next指针到需要逆置的最后一个元素的下一个节点
	for (int i = 0; i < end - begin + 2; i++)
		next = next->next;
	LNode* top = pre->next;//top指针指向需要逆置的首个元素
	LNode* cur = top;
	for (++count; count; count--) {//开始逆置
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