#include<iostream>
using namespace std;

class LNode { //���࣬p��e�ֱ��ʾϵ����ָ��
public:
    int p;
    int e;
    LNode* next;
public:
    LNode();
};

LNode::LNode() { //��ĳ�ʼ��
    p = 0;
    e = 0;
    this->next = NULL;
}

class Llist { //����ʽ��
public:
    LNode* head;
public:
    Llist();
    void printList(); //��ӡ����ʽ
    bool insert(int p, int e); //��ָ�����������
    void addPolyn(Llist L); //����ʽ�ӷ�
    Llist multiPolyn(Llist L); //����ʽ����ĳ˷�
    Llist singleMulti(LNode* term); //����ʽ�����ʽ�ĳ˷�
};

Llist::Llist() { //����ʽ����ĳ�ʼ����ͷ����������洢������
    this->head = (LNode*)malloc(sizeof(LNode));
    this->head->p = 0;
    this->head->next = NULL;
}

void Llist::printList() { //��ӡ����ʽ������ϵ��Ϊ0������Բ���
    LNode* temp = this->head;
    for (int i = 0; i < this->head->p; i++) {
        temp = temp->next;
        if (temp->p != 0)
            cout << temp->p << ' ' << temp->e << ' ';
    }
    cout << endl;
}

bool Llist::insert(int p, int e) { //������Զ�����ָ���������
    LNode* newNode = (LNode*)malloc(sizeof(LNode));
    if (!newNode)
        return false;
    LNode* temp = this->head;
    for (; temp->next && e > temp->next->e;)//��ָ���ƶ���Ӧ�ò���Ľڵ��ǰһ���ڵ�
        temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
    newNode->p = p;
    newNode->e = e;
    this->head->p++;
    return true;
}

void Llist::addPolyn(Llist L) { //����ʽ�ӷ�
    LNode* rear = this->head;
    bool isInsert = 0;
    if (this->head->p == 0) { //���Ϊ�ձ���ֱ�ӽ���һ������ʽ��ÿһ�������β���
        for (LNode* cur = L.head->next; cur; cur = cur->next)
            this->insert(cur->p, cur->e);
        return;
    }
    for (int i = 0; i < this->head->p; i++)
        rear = rear->next;
    LNode* thisCur = this->head->next;
    for (LNode* cur = L.head->next; cur; cur = cur->next) {
        if (cur->e<thisCur->e || cur->e>rear->e) //���Ҫ��������ָ��С��ԭ�����������С��ָ������������ָ������ֱ�Ӳ���
            this->insert(cur->p, cur->e);
        else {
            isInsert = 0;
            for (LNode* temp = thisCur; temp; temp = temp->next) //ָ����ȣ���ϵ�����
                if (cur->e == temp->e) {
                    temp->p += cur->p;
                    isInsert = 1;
                    break;
                }
            if (isInsert == 0)//û��ָ����ȵ����ֱ�Ӳ���
                this->insert(cur->p, cur->e);
        }
    }
}

Llist Llist::singleMulti(LNode* term) { //����ʽ��һ����ĳ˷����������õĶ���ʽ
    Llist L;
    LNode* cur = this->head;
    for (int i = 0; i < this->head->p; i++) {
        cur = cur->next;
        L.insert(cur->p * term->p, cur->e + term->e);
    }
    return L;
}

Llist Llist::multiPolyn(Llist L) { //����ʽ�����ʽ�ĳ˷���ԭ����ʽ�ֱ�����һ������ʽ��ÿһ������ˣ�����ۼӲ�����
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