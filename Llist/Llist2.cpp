#include<iostream>
using namespace std;

class LNode { //项类，p、e分别表示系数与指数
public:
    int p;
    int e;
    LNode* next;
public:
    LNode();
};

LNode::LNode() { //项的初始化
    p = 0;
    e = 0;
    this->next = NULL;
}

class Llist { //多项式类
public:
    LNode* head;
public:
    Llist();
    void printList(); //打印多项式
    bool insert(int p, int e); //按指数升序插入项
    void addPolyn(Llist L); //多项式加法
    Llist multiPolyn(Llist L); //多项式与项的乘法
    Llist singleMulti(LNode* term); //多项式与多项式的乘法
};

Llist::Llist() { //多项式链表的初始化，头结点的数据域存储链表长度
    this->head = (LNode*)malloc(sizeof(LNode));
    this->head->p = 0;
    this->head->next = NULL;
}

void Llist::printList() { //打印多项式，其中系数为0的项忽略不计
    LNode* temp = this->head;
    for (int i = 0; i < this->head->p; i++) {
        temp = temp->next;
        if (temp->p != 0)
            cout << temp->p << ' ' << temp->e << ' ';
    }
    cout << endl;
}

bool Llist::insert(int p, int e) { //插入项，自动按照指数升序插入
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (!newNode)
        return false;
    LNode* temp = this->head;
    for (; temp->next && e > temp->next->e;)//将指针移动到应该插入的节点的前一个节点
        temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
    newNode->p = p;
    newNode->e = e;
    this->head->p++;
    return true;
}

void Llist::addPolyn(Llist L) { //多项式加法
    LNode* rear = this->head;
    bool isInsert = 0;
    if (this->head->p == 0) { //如果为空表，则直接将另一个多项式的每一个项依次插入
        for (LNode* cur = L.head->next; cur; cur = cur->next)
            this->insert(cur->p, cur->e);
        return;
    }
    for (int i = 0; i < this->head->p; i++)
        rear = rear->next;
    LNode* thisCur = this->head->next;
    for (LNode* cur = L.head->next; cur; cur = cur->next) {
        if (cur->e<thisCur->e || cur->e>rear->e) //如果要加入的项的指数小于原来表中项的最小的指数，大于最大的指数，则直接插入
            this->insert(cur->p, cur->e);
        else {
            isInsert = 0;
            for (LNode* temp = thisCur; temp; temp = temp->next) //指数相等，则系数相加
                if (cur->e == temp->e) {
                    temp->p += cur->p;
                    isInsert = 1;
                    break;
                }
            if (isInsert == 0)//没有指数相等的项，则直接插入
                this->insert(cur->p, cur->e);
        }
    }
}

Llist Llist::singleMulti(LNode* term) { //多项式与一个项的乘法，返回所得的多项式
    Llist L;
    LNode* cur = this->head;
    for (int i = 0; i < this->head->p; i++) {
        cur = cur->next;
        L.insert(cur->p * term->p, cur->e + term->e);
    }
    return L;
}

Llist Llist::multiPolyn(Llist L) { //多项式与多项式的乘法，原多项式分别与另一个多项式的每一个项相乘，结果累加并返回
    Llist result;
    for (LNode* cur = L.head->next; cur; cur = cur->next) {
        Llist temp = this->singleMulti(cur);
        result.addPolyn(temp);
    }
    return result;
}

int main() {
    Llist L1;
    Llist L2;
    int count = 0;
    cin >> count;
    for (int i = 0; i < count; i++) {
        int p, e;
        cin >> p >> e;
        L1.insert(p, e);
    }
    cin >> count;
    for (int i = 0; i < count; i++) {
        int p, e;
        cin >> p >> e;
        L2.insert(p, e);
    }
    int cmd = 0;
    cin >> cmd;
    Llist result;
    if (cmd) {
        result = L1.multiPolyn(L2);
        result.printList();
    }
    else {
        L1.addPolyn(L2);
        L1.printList();
    }
    return 0;
}