#include <iostream>
#include <queue>
using namespace std;

class BiTree {
public:
    char data;
    BiTree* lchild;
    BiTree* rchild;
public:
    BiTree();
};

BiTree::BiTree() {
    data = '\0';
    lchild = NULL;
    rchild = NULL;
}

BiTree* preCreate() {
    BiTree* T;
    char elem;
    cin >> elem;
    if (elem == '#')
        T = NULL;
    else {
        T = (BiTree*)malloc(sizeof(BiTree));
        T->data = elem;

        T->lchild = preCreate();
        T->rchild = preCreate();
    }
    return T;
}

void preOrderTraverse(BiTree* T) {
    if (T) {
        cout << T->data;
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}


void inOrderTraverse(BiTree* T) {
    if (T) {
        inOrderTraverse(T->lchild);
        cout << T->data;
        inOrderTraverse(T->rchild);
    }
}

void postOrderTraverse(BiTree* T) {
    if (T) {
        postOrderTraverse(T->lchild);
        postOrderTraverse(T->rchild);
        cout << T->data;
    }
}

void levelOrderTraverse(BiTree* T) {
    BiTree* p;
    queue<BiTree*> Q;
    if (T) {
        Q.push(T);
        while (!Q.empty()) {
            p = Q.front();
            cout << p->data;
            Q.pop();
            if (p->lchild)
                Q.push(p->lchild);
            if (p->rchild)
                Q.push(p->rchild);
        }
    }
}

void prtbtree(BiTree* p, int cur)//逆时针旋转90度输出二叉树
{
    if (p)
    {
        prtbtree(p->rchild, cur + 1);
        for (int i = 0; i < cur; i++)
            cout << "     ";
        cout << p->data;
        cout << '\n';
        prtbtree(p->lchild, cur + 1);
    }
}

int main() {
    BiTree* T = preCreate();
    preOrderTraverse(T);
    cout << '\n';
    inOrderTraverse(T);
    cout << '\n';
    postOrderTraverse(T);
    cout << '\n';
    levelOrderTraverse(T);
    cout << '\n';
    prtbtree(T, 0);
    return 0;
}