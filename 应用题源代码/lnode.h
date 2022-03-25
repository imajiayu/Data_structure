#ifndef LNODE_H
#define LNODE_H

#include <QPushButton>

class LNode//节点类，以链表方式存储节点
{
public:
    QPushButton* but;//该节点所对应的按钮
    LNode* next;//下一个节点
    LNode();
};

#endif // LNODE_H
